package quickfix.banzai.ui;

import org.apache.log4j.Category;

import quickfix.banzai.OrderTableModel;
import quickfix.banzai.ExecutionTableModel;
import quickfix.banzai.BanzaiApplication;

import javax.swing.*;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

/**
 *  Main application window
 */
public class BanzaiFrame extends JFrame {

    /** enable logging for this class */
    private static Category log = Category.getInstance
                                  (BanzaiFrame.class.getName());

    public BanzaiFrame(OrderTableModel orderTableModel,
                       ExecutionTableModel executionTableModel,
                       BanzaiApplication application) {
        super();
        setTitle("BrASM");
        setSize(450, 350);
        getContentPane().add(new BanzaiPanel(orderTableModel,
                                             executionTableModel,
                                             application),
                             BorderLayout.CENTER);
        setVisible(true);
    }
}
