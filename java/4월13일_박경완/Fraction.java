import java.util.Scanner;
public class Fraction {
    int numerator;
    int denominator;
    public Fraction(){
        numerator=1 ;
        denominator = 1;
    }
    public Fraction(int d){
        numerator = 1;
        denominator = d;
    }
    public Fraction(int n, int d){
        numerator = n;
        denominator = d;
    }

    public void addFraction(Fraction f1,Fraction f2){
        this.numerator =((f1.numerator*f2.denominator)+(f2.numerator*f1.denominator));
        this.denominator = f1.denominator*f2.denominator;
    }
    public void subFraction(Fraction f1,Fraction f2){
        this.numerator =((f1.numerator*f2.denominator)-(f2.numerator*f1.denominator));
        this.denominator = f1.denominator*f2.denominator;
    }
    public void mulFraction(Fraction f1,Fraction f2){
        this.numerator =f1.numerator*f2.numerator;
        this.denominator = f1.denominator*f2.denominator;
    }
    public void divFraction(Fraction f1,Fraction f2){
        this.numerator =f1.numerator*f2.denominator;
        this.denominator = f1.denominator*f2.numerator;
    }
    public void printFraction(){
        System.out.print(this.numerator+"/"+this.denominator);
    }

    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
        int n,d;
        System.out.print("분수1(분자 분모) 입력: ");
        n = sc.nextInt();
        d = sc.nextInt();
        Fraction f1 = new Fraction(n,d);
        System.out.print("분수2(분자 분모) 입력: ");
        n = sc.nextInt();
        d = sc.nextInt();
        Fraction f2 = new Fraction(n,d);
        Fraction answer = new Fraction();
        System.out.println("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓");

        answer.addFraction(f1,f2);
        f1.printFraction();System.out.print("+");f2.printFraction();System.out.print("=");answer.printFraction();
        System.out.print("\n");

        answer.subFraction(f1,f2);
        f1.printFraction();System.out.print("-");f2.printFraction();System.out.print("=");answer.printFraction();
        System.out.print("\n");

        answer.mulFraction(f1,f2);
        f1.printFraction();System.out.print("*");f2.printFraction();System.out.print("=");answer.printFraction();
        System.out.print("\n");

        answer.divFraction(f1,f2);
        f1.printFraction();System.out.print("/");f2.printFraction();System.out.print("=");answer.printFraction();
    }

}
