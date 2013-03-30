
package quickfix.banzai.ui;

import org.apache.log4j.Category;
import org.apache.log4j.PatternLayout;
import quickfix.banzai.Order;
import quickfix.banzai.OrderTableModel;
import quickfix.banzai.ExecutionTableModel;
import quickfix.banzai.BanzaiApplication;

import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.Observer;
import java.util.Observable;

/**
 *  Main content panel
 */
public class BanzaiPanel extends JPanel
    implements Observer, ActionListener {

    private static Category log =
        Category.getInstance(BanzaiPanel.class.getName());

    private OrderEntryPanel orderEntryPanel = null;
    private OrderPanel orderPanel = null;
    private ExecutionPanel executionPanel = null;
    private CancelReplacePanel cancelReplacePanel = null;
    private OrderTableModel orderTableModel = null;

    public BanzaiPanel(OrderTableModel orderTableModel,
                       ExecutionTableModel executionTableModel,
                       BanzaiApplication application) {
        setName("BanzaiPanel");
        this.orderTableModel = orderTableModel;

        setBorder(BorderFactory.createEmptyBorder(5, 5, 5, 5));
        setLayout(new GridBagLayout());
        GridBagConstraints constraints = new GridBagConstraints();
        constraints.fill = GridBagConstraints.BOTH;
        constraints.weightx = 1;

        orderEntryPanel = new OrderEntryPanel(orderTableModel, application);
        constraints.insets = new Insets(0, 0, 5, 0);
        add(orderEntryPanel, constraints);

        constraints.gridx++;
        constraints.weighty = 10;

        JTabbedPane tabbedPane = new JTabbedPane();
        orderPanel = new OrderPanel(orderTableModel, application);
        executionPanel = new ExecutionPanel(executionTableModel);

        tabbedPane.add("Ordens", orderPanel);
        tabbedPane.add("Execuções", executionPanel);
        add(tabbedPane, constraints);

        cancelReplacePanel = new CancelReplacePanel(application);
        constraints.weighty = 0;
        add(cancelReplacePanel, constraints);
        cancelReplacePanel.setEnabled(false);

        orderEntryPanel.addActionListener(this);
        orderPanel.orderTable().getSelectionModel()
        .addListSelectionListener(new OrderSelection());
        cancelReplacePanel.addActionListener(this);
        application.addOrderObserver(this);
    }

    public void update(Observable o, Object arg) {
        cancelReplacePanel.update();
    }

    public void actionPerformed(ActionEvent e) {
        ListSelectionModel selection =
            orderPanel.orderTable().getSelectionModel();
        selection.clearSelection();
    }

    private class OrderSelection implements ListSelectionListener {
        public void valueChanged(ListSelectionEvent e) {
            ListSelectionModel selection =
                orderPanel.orderTable().getSelectionModel();
            if(selection.isSelectionEmpty()) {
                orderEntryPanel.clearMessage();
                return;
            }

            int firstIndex = e.getFirstIndex();
            int lastIndex = e.getLastIndex();
            int selectedRow = 0;
            int numSelected = 0;

            for(int i = firstIndex; i <= lastIndex; ++i) {
                if(selection.isSelectedIndex(i)) {
                    selectedRow = i;
                    numSelected++;
                }
            }

            if(numSelected > 1)
                orderEntryPanel.clearMessage();
            else {
                Order order = (Order)orderTableModel.getOrder(selectedRow);
                if(order != null) {
                    orderEntryPanel.setMessage(order.getMessage());
                    cancelReplacePanel.setOrder(order);
                }
            }
        }
    }
}
