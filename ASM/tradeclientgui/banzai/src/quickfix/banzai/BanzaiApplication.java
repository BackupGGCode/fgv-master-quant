package quickfix.banzai;

import java.util.Date;
import java.util.Observable;
import java.util.Observer;
import java.util.Set;
import java.util.HashSet;
import java.util.Map;
import java.util.HashMap;
import quickfix.*;
import quickfix.banzai.Order;
import quickfix.field.*;
import javax.swing.SwingUtilities;

public class BanzaiApplication implements Application {
    private OrderTableModel orderTableModel = null;
    private ExecutionTableModel executionTableModel = null;
    private ObservableOrder observableOrder = new ObservableOrder();
    private ObservableLogon observableLogon = new ObservableLogon();
    static private TwoWayMap sideMap = new TwoWayMap();
    static private TwoWayMap typeMap = new TwoWayMap();
    static private TwoWayMap tifMap = new TwoWayMap();
    static private HashMap execIDs = new HashMap();

    public BanzaiApplication(OrderTableModel orderTableModel,
                             ExecutionTableModel executionTableModel) {
        this.orderTableModel = orderTableModel;
        this.executionTableModel = executionTableModel;
    }

    public void onCreate(SessionID sessionID) {}
    public void onLogon(SessionID sessionID) {
        observableLogon.logon(sessionID);
    }
    public void onLogout(SessionID sessionID) {
        observableLogon.logout(sessionID);
    }

    public void toAdmin(quickfix.Message message,
                        SessionID sessionID) {}

    public void toApp(quickfix.Message message,
                      SessionID sessionID) throws DoNotSend {}

    public void fromAdmin(quickfix.Message message,SessionID sessionID)
    throws FieldNotFound, IncorrectDataFormat, IncorrectTagValue, RejectLogon {}

    public void fromApp(quickfix.Message message, SessionID sessionID)
    throws FieldNotFound, IncorrectDataFormat, IncorrectTagValue, UnsupportedMessageType {
        try {
            SwingUtilities.invokeLater(new doFromApp(message, sessionID));
        } catch(Exception e) {}
    }

    public class doFromApp implements Runnable {
        private quickfix.Message message;
        private SessionID sessionID;

        public doFromApp(quickfix.Message message, SessionID sessionID) {
            this.message = message;
            this.sessionID = sessionID;
        }

        public void run() {
            try {
                MsgType msgType = new MsgType();
                if(message.getHeader().getField(msgType).valueEquals("8"))
                    executionReport(message, sessionID);
                if(message.getHeader().getField(msgType).valueEquals("9"))
                    cancelReject(message, sessionID);
            } catch(FieldNotFound e) {
                System.out.println(e);
            }
        }
    }

    private void executionReport(Message message, SessionID sessionID)
    throws FieldNotFound {

        ExecID execID = (ExecID)message.getField(new ExecID());
        if(alreadyProcessed(execID, sessionID))
            return;

        String id = message.getField(new ClOrdID()).getValue();
        Order order = orderTableModel.getOrder(id);
        if(order == null)
            return;

        LastShares lastShares = new LastShares(0);

        try {
            OrderQty orderQty = (OrderQty)message.getField(new OrderQty());
            int diff = order.getQuantity() - (int)orderQty.getValue();
            order.setQuantity((int)orderQty.getValue());
            order.setOpen(order.getOpen() - diff);
        } catch(FieldNotFound e) {}
        try {
            Price price = (Price)message.getField(new Price());
            order.setLimit(new Double(price.getValue()));
        } catch(FieldNotFound e) {}
        try {
            message.getField(lastShares);
        } catch(FieldNotFound e) {}

        if(lastShares.getValue() > 0) {
            order.setExecuted((int)message.getField(new CumQty()).getValue());
            order.setAvgPx(message.getField(new AvgPx()).getValue());
        }
        OrdStatus ordStatus = (OrdStatus)message.getField(new OrdStatus());

        try {
            order.setOpen((int)message.getField(new LeavesQty()).getValue());
        } catch(FieldNotFound e) {
            // FIX40 doesn't have LeavesQty
            if(ordStatus.valueEquals(OrdStatus.REJECTED) ||
                    ordStatus.valueEquals(OrdStatus.CANCELED))
                order.setOpen(0);
            else if(ordStatus.valueEquals(OrdStatus.NEW)) {
                if(order.isNew()) {
                    order.setOpen(order.getQuantity());
                    order.setNew(false);
                }
            }
            order.setOpen(order.getOpen() - (int)lastShares.getValue());
        }

        if(ordStatus.valueEquals(OrdStatus.REJECTED))
            order.setRejected(true);
        else if(ordStatus.valueEquals(OrdStatus.CANCELED) ||
                ordStatus.valueEquals(OrdStatus.DONE_FOR_DAY))
            order.setCanceled(true);

        try {
            order.setMessage(message.getField(new Text()).getValue());
        } catch(FieldNotFound e) {
            order.setMessage(null);
        }

        orderTableModel.updateOrder(order, id);
        observableOrder.update(order);

        if(lastShares.getValue() > 0) {
            Execution execution = new Execution();
            execution.setExchangeID(sessionID + message.getField(new ExecID()).getValue());
            execution.setSymbol(message.getField(new Symbol()).getValue());
            execution.setQuantity((int)lastShares.getValue());
            execution.setPrice(message.getField(new LastPx()).getValue());
            Side side = (Side)message.getField(new Side());
            execution.setSide(FIXSideToSide(side));
            executionTableModel.addExecution(execution);
        }
    }

    private void cancelReject(Message message, SessionID sessionID)
    throws FieldNotFound {

        String id = message.getField(new ClOrdID()).getValue();
        Order order = orderTableModel.getOrder(id);
        if(order == null)
            return;
        if(order.getOriginalID() != null)
            order = orderTableModel.getOrder(order.getOriginalID());

        try {
            order.setMessage(message.getField(new Text()).getValue());
        } catch(FieldNotFound e) {}
        orderTableModel.updateOrder(order, order.getID());
    }

    private boolean alreadyProcessed(ExecID execID, SessionID sessionID) {
        HashSet set = (HashSet)execIDs.get(sessionID);
        if(set == null) {
            set = new HashSet();
            set.add(execID);
            execIDs.put(sessionID, set);
            return false;
        } else {
            if(set.contains(execID))
                return true;
            set.add(execID);
            return false;
        }
    }

    private void send(quickfix.Message message, SessionID sessionID) {
        try {
            Session.sendToTarget(message, sessionID);
        } catch(SessionNotFound e) {
            System.out.println(e);
        }
    }

    public void send(Order order) throws IllegalArgumentException {
        String beginString = order.getSessionID().getBeginString();
        send42(order);
        return;
    }

    public void send42(Order order) {
        quickfix.fix42.NewOrderSingle newOrderSingle =
            new quickfix.fix42.NewOrderSingle
            (new ClOrdID(order.getID()),
             new HandlInst('1'),
             new Symbol(order.getSymbol()),
             sideToFIXSide(order.getSide()),
             new TransactTime(),
             typeToFIXType(order.getType()));
        newOrderSingle.set(new OrderQty(order.getQuantity()));

        send(populateOrder(order, newOrderSingle), order.getSessionID());
    }

  

    public quickfix.Message populateOrder
    (Order order, quickfix.Message newOrderSingle) {

        OrderType type = order.getType();
        newOrderSingle.setField(new Price(order.getLimit().doubleValue()));
        
        return newOrderSingle;
    }

    public void cancel(Order order) {
        String beginString = order.getSessionID().getBeginString();
        cancel42(order);
        return;
    }

    public void cancel42(Order order) {
        String id = order.generateID();
        quickfix.fix42.OrderCancelRequest message =
            new quickfix.fix42.OrderCancelRequest
            (new OrigClOrdID(order.getID()),
             new ClOrdID(id),
             new Symbol(order.getSymbol()),
             sideToFIXSide(order.getSide()),
             new TransactTime());
        message.setField(new OrderQty(order.getQuantity()));

        orderTableModel.addID(order, id);
        send(message, order.getSessionID());
    }

    
    public void replace(Order order, Order newOrder) {
        String beginString = order.getSessionID().getBeginString();
        replace42(order, newOrder);
        return;
    }

    public void replace42(Order order, Order newOrder) {
        quickfix.fix42.OrderCancelReplaceRequest message =
            new quickfix.fix42.OrderCancelReplaceRequest
            (new OrigClOrdID(order.getID()),
             new ClOrdID(newOrder.getID()),
             new HandlInst('1'),
             new Symbol(order.getSymbol()),
             sideToFIXSide(order.getSide()),
             new TransactTime(),
             typeToFIXType(order.getType()));

        orderTableModel.addID(order, newOrder.getID());
        send(populateCancelReplace(order, newOrder,
                                   message), order.getSessionID());
    }
    
    Message populateCancelReplace(Order order, Order newOrder,
                                  quickfix.Message message) {

        if(order.getQuantity() != newOrder.getQuantity())
            message.setField(new OrderQty(newOrder.getQuantity()));
        if(order.getLimit() != newOrder.getLimit())
            message.setField(new Price(newOrder.getLimit().doubleValue()));
        return message;
    }

    public  Side sideToFIXSide(OrderSide side) {
        return (Side)sideMap.getFirst(side);
    }
    public  OrderSide FIXSideToSide(Side side) {
        return (OrderSide)sideMap.getSecond(side);
    }

    public  OrdType typeToFIXType(OrderType type) {
        return (OrdType)typeMap.getFirst(type);
    }
    public  OrderType FIXTypeToType(OrdType type) {
        return (OrderType)typeMap.getSecond(type);
    }

    public void addLogonObserver(Observer observer) {
        observableLogon.addObserver(observer);
    }
    public void deleteLogonObserver(Observer observer) {
        observableLogon.deleteObserver(observer);
    }
    public void addOrderObserver(Observer observer) {
        observableOrder.addObserver(observer);
    }
    public void deleteOrderObserver(Observer observer) {
        observableOrder.deleteObserver(observer);
    }

    public class ObservableOrder extends Observable {
        public void update(Order order) {
            setChanged();
            notifyObservers(order);
            clearChanged();
        }
    }

    public class ObservableLogon extends Observable {
        private HashSet set = new HashSet();

        public void logon(SessionID sessionID) {
            set.add(sessionID);
            setChanged();
            notifyObservers(new LogonEvent(sessionID, true));
            clearChanged();
        }
        public void logout(SessionID sessionID) {
            set.remove(sessionID);
            setChanged();
            notifyObservers(new LogonEvent(sessionID, false));
            clearChanged();
        }
    }

    static {
        sideMap.put(OrderSide.BUY, new Side(Side.BUY));
        sideMap.put(OrderSide.SELL, new Side(Side.SELL));
        typeMap.put(OrderType.LIMIT, new OrdType(OrdType.LIMIT));
    }
}
