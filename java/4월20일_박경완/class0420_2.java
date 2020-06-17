import java.util.Scanner;

public class class0420_2 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while(true) {
            System.out.print("두 정수와 연산자를 입력하시오>> ");
            int x = sc.nextInt();
            int y = sc.nextInt();
            String what = sc.next();

            Add a = new Add();
            Sub s = new Sub();
            Mul m = new Mul();
            Div d = new Div();

            switch (what){
                case "+":
                    a.setValue(x,y);
                    System.out.println(a.calculate());
                    break;
                case "-":
                    s.setValue(x,y);
                    System.out.println(s.calculate());
                    break;
                case "*":
                    m.setValue(x,y);
                    System.out.println(m.calculate());
                    break;
                case "/":
                    d.setValue(x,y);
                    System.out.println(d.calculate());
                    break;
                default:
                    System.out.println("프로그램을 종료합니다.");
                    return;

            }

        }
    }

}

class Calc {
    public int a,b;
    void setValue(int a,int b) {
        this.a = a;
        this.b = b;
    }
}

class Add extends Calc {
    int calculate() { return this.a+this.b; }
}

class Sub extends Calc {
    int calculate() { return this.a-this.b; }
}

class Mul extends Calc {
    int calculate() { return this.a*this.b; }
}

class Div extends Calc {
    int calculate() { return this.a/this.b; }
}

