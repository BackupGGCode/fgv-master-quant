package quickfix.banzai.ui;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import quickfix.banzai.*;

public class CancelReplacePanel extends JPanel {

    private JButton cancelButton = new JButton("Cancelar");
    private Order order = null;

    private GridBagConstraints constraints = new GridBagConstraints();

    private BanzaiApplication application;

    public CancelReplacePanel(final BanzaiApplication application) {
        this.application = application;
        cancelButton.addActionListener(new CancelListener());

        setLayout(new GridBagLayout());
        createComponents();
    }

    public void addActionListener(ActionListener listener) {
        cancelButton.addActionListener(listener);
    }

    private void createComponents() {
        //constraints.fill = GridBagConstraints.BOTH;
        //constraints.weightx = 1;

        //int x = 0;
        //int y = 0;

        constraints.insets = new Insets(0, 0, 5, 5);
        add(cancelButton, 0, 0);

    }

    public void setEnabled(boolean enabled) {
        cancelButton.setEnabled(enabled);
        Color labelColor = enabled ? Color.black : Color.gray;
        Color bgColor = enabled ? Color.white : Color.gray;

    }

    public void update() {
        setOrder(this.order);
    }

    public void setOrder(Order order) {
        if(order == null)
            return;
        this.order = order;

        Double limit = order.getLimit();

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

}
