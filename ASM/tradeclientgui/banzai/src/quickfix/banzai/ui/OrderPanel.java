package quickfix.banzai.ui;

import org.apache.log4j.Category;
import quickfix.banzai.OrderTableModel;
import quickfix.banzai.BanzaiApplication;
import javax.swing.*;
import javax.swing.table.TableModel;
import java.awt.*;
import java.util.ArrayList;

/**
 *  Contains the Order table.
 */
public class OrderPanel extends JPanel {

    private static Category log =
        Category.getInstance(OrderPanel.class.getName());

    private JTable orderTable = null;

    public OrderPanel(OrderTableModel orderTableModel,
                      BanzaiApplication application) {
        setBorder(BorderFactory.createEmptyBorder(5, 5, 5, 5));
        setLayout(new GridBagLayout());
        GridBagConstraints constraints = new GridBagConstraints();
        constraints.fill = GridBagConstraints.BOTH;
        constraints.weightx = 1;
        constraints.weighty = 1;

        orderTable = new OrderTable(orderTableModel, application);
        add(new JScrollPane(orderTable), constraints);
    }

    public JTable orderTable() {
        return orderTable;
    }
}
