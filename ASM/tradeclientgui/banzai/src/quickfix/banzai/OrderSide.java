package quickfix.banzai;
import java.util.HashMap;
import java.util.Map;

public class OrderSide {
    static private Map known = new HashMap();
    static public final OrderSide BUY = new OrderSide("Compra");
    static public final OrderSide SELL = new OrderSide("Venda");
    static private OrderSide[] array = { BUY, SELL };


    private String name;

    private OrderSide(String name) {
        this.name = name;
        synchronized(OrderSide.class) {
            known.put(name, this);
        }
    }

    public String getName() {
        return name;
    }

    public String toString() {
        return name;
    }

    static public Object[] toArray() {
        return array;
    }

    public static OrderSide parse(String type)
    throws IllegalArgumentException {
        OrderSide result = (OrderSide)known.get(type);
        if(result == null) {
            throw new IllegalArgumentException
            ("OrderSide:  " + type + " is unknown.");
        }
        return result;
    }
}
