package quickfix.banzai;

import java.util.Map;
import java.util.HashMap;

public class TwoWayMap {
    private HashMap firstToSecond = new HashMap();
    private HashMap secondToFirst = new HashMap();

    public void put(Object first, Object second) {
        firstToSecond.put(first, second);
        secondToFirst.put(second, first);
    }

    public Object getFirst(Object first) {
        return firstToSecond.get(first);
    }

    public Object getSecond(Object second) {
        return secondToFirst.get(second);
    }

    public String toString() {
        return firstToSecond.toString() + "\n" + secondToFirst.toString();
    }
}
