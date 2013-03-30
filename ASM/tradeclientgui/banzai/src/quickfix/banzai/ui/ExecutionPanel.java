package quickfix.banzai.ui;

import org.apache.log4j.Category;
import quickfix.banzai.ExecutionTableModel;

import javax.swing.*;
import java.awt.*;

/**
 *  Contains the executions panel
 */
public class ExecutionPanel extends JPanel {

    /** enable logging for this class */
    private static Category log
    = Category.getInstance(ExecutionPanel.class.getName());

    public ExecutionPanel(ExecutionTableModel executionTableModel) {
        setBorder(BorderFactory.createEmptyBorder(5, 5, 5, 5));
        setLayout(new GridBagLayout());
        GridBagConstraints constraints = new GridBagConstraints();
        constraints.fill = GridBagConstraints.BOTH;
        constraints.weightx = 1;
        constraints.weighty = 1;

        JTable table = new ExecutionTable(executionTableModel);
        add(new JScrollPane(table), constraints);
    }

}
