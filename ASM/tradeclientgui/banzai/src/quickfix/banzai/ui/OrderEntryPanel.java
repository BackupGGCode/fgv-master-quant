package quickfix.banzai.ui;

import java.util.Observable;
import java.util.Observer;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.border.LineBorder;
import javax.swing.JOptionPane;
import quickfix.banzai.*;
import quickfix.SessionID;

public class OrderEntryPanel extends JPanel implements Observer {
    private boolean symbolEntered = true;
    private boolean quantityEntered = false;
    private boolean limitEntered = true;
    private boolean sessionEntered = false;

    private JTextField symbolTextField = new JTextField("FGV");
    private IntegerNumberTextField quantityTextField =
        new IntegerNumberTextField();

    private JComboBox sideComboBox = new JComboBox(OrderSide.toArray());

    private DoubleNumberTextField limitPriceTextField =
        new DoubleNumberTextField();
    private DoubleNumberTextField stopPriceTextField =
        new DoubleNumberTextField();

    private JComboBox sessionComboBox = new JComboBox();

    private JLabel limitPriceLabel = new JLabel("Preço");

    private JLabel messageLabel = new JLabel(" ");
    private JButton submitButton = new JButton("Enviar");

    private OrderTableModel orderTableModel = null;
    private BanzaiApplication application = null;

    private GridBagConstraints constraints = new GridBagConstraints();

    public OrderEntryPanel(final OrderTableModel orderTableModel,
                           final BanzaiApplication application) {
        setName("OrderEntryPanel");
        this.orderTableModel = orderTableModel;
        this.application = application;

        application.addLogonObserver(this);

        SubmitActivator activator = new SubmitActivator();
        symbolTextField.addKeyListener(activator);
        quantityTextField.addKeyListener(activator);
        limitPriceTextField.addKeyListener(activator);
        stopPriceTextField.addKeyListener(activator);
        sessionComboBox.addItemListener(activator);

        setBorder(BorderFactory.createEmptyBorder(5, 0, 5, 0));
        setLayout(new GridBagLayout());
        createComponents();
    }

    public void addActionListener(ActionListener listener) {
        submitButton.addActionListener(listener);
    }

    public void setMessage(String message) {
        messageLabel.setText(message);
        if(message == null || message.equals(""))
            messageLabel.setText(" ");
    }

    public void clearMessage() {
        setMessage(null);
    }

    private void createComponents() {
        constraints.fill = GridBagConstraints.BOTH;
        constraints.weightx = 1;

        int x = 0;
        int y = 0;

        add(new JLabel("Ticker"), x, y);
        add(new JLabel("Quantidade"), ++x, y );
        add(new JLabel("Tipo"), ++x, y );
        constraints.ipadx = 30;
        add(limitPriceLabel, ++x, y );

        symbolTextField.setName("SymbolTextField");
        add(symbolTextField, x=0, ++y);
        constraints.ipadx = 0;
        quantityTextField.setName("QuantityTextField");
        add(quantityTextField, ++x, y);
        sideComboBox.setName("SideComboBox");
        add(sideComboBox, ++x, y);
        limitPriceTextField.setName("LimitPriceTextField");
        add(limitPriceTextField, ++x, y);

        constraints.insets = new Insets(3, 0, 0, 0);
        constraints.gridwidth = GridBagConstraints.RELATIVE;
        sessionComboBox.setName("SessionComboBox");
        add(sessionComboBox, 0, ++y);
        constraints.gridwidth = GridBagConstraints.REMAINDER;
        submitButton.setName("SubmitButton");
        add(submitButton, x, y);
        constraints.gridwidth = 0;
        add(messageLabel, 0, ++y);

        Font font = new Font(messageLabel.getFont().getFontName(),
                             Font.BOLD, 12);
        messageLabel.setFont(font);
        messageLabel.setForeground(Color.red);
        messageLabel.setHorizontalAlignment(JLabel.CENTER);
        submitButton.setEnabled(true);
        submitButton.addActionListener(new SubmitListener());
        activateSubmit();
    }

    private JComponent add(JComponent component, int x, int y) {
        constraints.gridx = x;
        constraints.gridy = y;
        add(component, constraints);
        return component;
    }

    private void activateSubmit() {
        boolean activate = symbolEntered && quantityEntered
                           && sessionEntered;
        
        submitButton.setEnabled(activate && limitEntered);
    }

    private class PriceListener implements ItemListener {
        public void itemStateChanged(ItemEvent e) {
        	
            enableLimitPrice(true);
            enableStopPrice(false);
        	
            activateSubmit();
        }

        private void enableLimitPrice(boolean enabled) {
            Color labelColor = enabled ? Color.black : Color.gray;
            Color bgColor = enabled ? Color.white : Color.gray;
            limitPriceTextField.setEnabled(enabled);
            limitPriceTextField.setBackground(bgColor);
            limitPriceLabel.setForeground(labelColor);
        }

        private void enableStopPrice(boolean enabled) {
            Color labelColor = enabled ? Color.black : Color.gray;
            Color bgColor = enabled ? Color.white : Color.gray;
            stopPriceTextField.setEnabled(enabled);
            stopPriceTextField.setBackground(bgColor);
        }
    }

    public void update(Observable o, Object arg) {
        LogonEvent logonEvent = (LogonEvent)arg;
        if(logonEvent.isLoggedOn())
            sessionComboBox.addItem(logonEvent.getSessionID());
        else
            sessionComboBox.removeItem(logonEvent.getSessionID());
    }

    private class SubmitListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            Order order = new Order();
            order.setSide((OrderSide) sideComboBox.getSelectedItem());
            order.setType(OrderType.LIMIT);

            order.setSymbol(symbolTextField.getText());
            order.setQuantity(Integer.parseInt
                              (quantityTextField.getText()));

            OrderType type = order.getType();
            order.setLimit(limitPriceTextField.getText());
            order.setSessionID((SessionID)sessionComboBox.getSelectedItem());

            orderTableModel.addOrder(order);
            
            try {
              application.send(order);
            } catch(IllegalArgumentException ex) {
              JOptionPane.showMessageDialog(null,
                  ex.getMessage(),
                  "Failed to send message",
                  JOptionPane.ERROR_MESSAGE);
            }
        }
    }

    private class SubmitActivator
        implements KeyListener, ItemListener {
        public void keyReleased(KeyEvent e) {
            Object obj = e.getSource();
            if(obj == symbolTextField) {
                symbolEntered = testField(obj);
            } else if(obj == quantityTextField) {
                quantityEntered = testField(obj);
            } else if(obj == limitPriceTextField) {
                limitEntered = testField(obj);
            }
            activateSubmit();
        }

        public void itemStateChanged(ItemEvent e) {
            sessionEntered = sessionComboBox.getSelectedItem() != null;
            activateSubmit();
        }

        private boolean testField(Object o) {
            String value = ((JTextField)o).getText();
            value.trim();
            return value.length() > 0;
        }

        public void keyTyped(KeyEvent e) {}
        public void keyPressed(KeyEvent e) {}
    }
}
