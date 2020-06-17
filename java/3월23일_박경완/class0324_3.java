import java.util.Scanner;
public class class0324_3 {
    public static void main(String args[]){
        Scanner sc =new Scanner(System.in);
        System.out.print("원화를 입력하시오(단위 원):");
        int won = sc.nextInt();
        System.out.printf("%d원은 %f달러",won,won/1280.00);
    }
}
