public class class0420_1 {
    public static void main(String args[]){
        SharpPencil sp = new SharpPencil();
        BallPen bp = new BallPen();
        FountainPen fp = new FountainPen();

        sp.setAmount(2);
        bp.setColor("ivory");
        bp.setAmount(5);
        fp.setColor("brown");
        fp.setAmount(1);
        System.out.printf("샤프 : %d 만큼 남았습니다\n"+
                            "볼펜 : %s 컬러, %d 만큼 남았습니다.\n"+
                            "만년필 : %s 컬러, %d 만큼 남았습니다.\n"
                            ,sp.getAmount(),bp.getColor(),bp.getAmount(),fp.getColor(),fp.getAmount());


    }
}

class escribulator{
    private int amount;
    public int getAmount(){return amount;}
    public void setAmount(int amount){this.amount = amount;}
}

class SharpPencil extends escribulator{
    private int width;
}

class BallPen extends escribulator{
    private String color;
    public String getColor(){return color;}
    public void setColor(String color){this.color =color;}

}
class FountainPen extends BallPen{
    public void refill(int n){ this.setAmount(n);}
}
