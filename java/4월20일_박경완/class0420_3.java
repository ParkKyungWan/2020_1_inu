public class class0420_3 {
    public static void main(String args[]){
        IPTV iptv = new IPTV("192.168.0.1", 99, 2020);
        iptv.printProperty();
    }
}
class TV{
    private int size;
    public TV(){}
    public TV(int size){this.size = size;}
    protected int getSize(){return size;}
}
class ColorTV extends TV{
    private int Color;
    public ColorTV(){}
    public ColorTV(int size,int Color){
        super(size);
        this.Color = Color;
    }
    protected int getColor(){return Color;}
}
class IPTV extends  ColorTV {
    private String IP;

    public IPTV(String IP, int size, int Color) {
        super(size, Color);
        this.IP = IP;
    }

    protected String getIP() {
        return IP;
    }

    public void printProperty() {
        System.out.println("나의 IPTV는 "
                + this.getIP() + " 주소의 "
                + this.getSize() + " 인치"
                + this.getColor() + " 컬러");
    }
}
