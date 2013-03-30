package quickfix.banzai.ui;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import quickfix.banzai.*;

public class CancelReplacePanel extends JPanel {
    private JLabel quantityLabel = new JLabel("Quantidade");
    private JLabel limitPriceLabel = new JLabel("Preço");
    private IntegerNumberTextField  quantityTextField =
        new IntegerNumberTextField();
    private DoubleNumberTextField limitPriceTextField =
        new DoubleNumberTextField();
    private JButton cancelButton = new JButton("Cancelar");
    private JButton replaceButton = new JButton("Trocar");
    private Order order = null;

    private GridBagConstraints constraints = new GridBagConstraints();

    private BanzaiApplication application;

    public CancelReplacePanel(final BanzaiApplication application) {
        this.application = application;
        cancelButton.addActionListener(new CancelListener());
        replaceButton.addActionListener(new ReplaceListener());

        setLayout(new GridBagLayout());
        createComponents();
    }

    public void addActionListener(ActionListener listener) {
        cancelButton.addActionListener(listener);
        replaceButton.addActionListener(listener);
    }

    private void createComponents() {
        constraints.fill = GridBagConstraints.BOTH;
        constraints.weightx = 1;

        int x = 0;
        int y = 0;

        constraints.insets = new Insets(0, 0, 5, 5);
        add(cancelButton, x, y);
        add(replaceButton, ++x, y);
        constraints.weightx = 0;
        add(quantityLabel, ++x, y);
        constraints.weightx = 5;
        add(quantityTextField, ++x, y);
        constraints.weightx = 0;
        add(limitPriceLabel, ++x, y);
        constraints.weightx = 5;
        add(limitPriceTextField, ++x, y);
    }

    public void setEnabled(boolean enabled) {
        cancelButton.setEnabled(enabled);
        replaceButton.setEnabled(enabled);
        quantityTextField.setEnabled(enabled);
        limitPriceTextField.setEnabled(enabled);

        Color labelColor = enabled ? Color.black : Color.gray;
        Color bgColor = enabled ? Color.white : Color.gray;
        quantityTextField.setBackground(bgColor);
        limitPriceTextField.setBackground(bgColor);
        quantityLabel.setForeground(labelColor);
        limitPriceLabel.setForeground(labelColor);
    }

    public void update() {
        setOrder(this.order);
    }

    public void setOrder(Order order) {
        if(order == null)
            return;
        this.order = order;
        quantityTextField.setText
        (new Integer(order.getOpen()).toString());

        Double limit = order.getLimit();
        if(limit != null)
            limitPriceTextField.setText(order.getLimit().toString());
        setEnabled(order.getOpen() > 0);
    }

    private JComponent add(JComponent component, int x, int y) {
        constraints.gridx = x;
        constraints.gridy = y;
        add(component, constraints);
        return component;
    }

    private class CancelListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            application.cancel(order);
        }
    }

    private class ReplaceListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            Order newOrder = (Order)order.clone();
            newOrder.setQuantity
            (Integer.parseInt(quantityTextField.getText()));
            newOrder.setLimit
            (new Double(limitPriceTextField.getText()));
            newOrder.setRejected(false);
            newOrder.setCanceled(false);
            newOrder.setOpen(0);
            newOrder.setExecuted(0);

            application.replace(order, newOrder);
        }
    }
}
