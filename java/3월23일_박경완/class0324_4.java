import java.util.Scanner;
public class class0324_4 {
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
        boolean check = true;
        while(check){

            int i = sc.nextInt();
            String m = sc.next();
            int j = sc.nextInt();

            if(m.equals("+")){
                System.out.printf("결과: %d\n",i+j);
            }else if(m.equals("-")) {
                System.out.printf("결과: %d\n",i-j);
            }else if(m.equals("*")) {
                System.out.printf("결과: %d\n",i*j);
            }else if(m.equals("/")) {
                System.out.printf("결과: %d\n",i/j);
            }else if(m.equals("%")) {
                System.out.printf("결과: %d\n",i%j);
            }else if(m.equals("=")) {
                check = false;
            }

        }
    }
}
