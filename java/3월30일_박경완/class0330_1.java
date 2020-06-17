import java.util.Scanner;

public class class0330_1 {
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
        int input_num = sc.nextInt();
        int clap = 0;

        //10의자리수 3,6,9 확인
        if(input_num/10 == 3 || input_num/10 == 6 ||input_num/10 == 9 ){
            clap++;
        }

        //1의자리수 3,6,9 확인
        if(input_num%10 == 3 || input_num%10 == 6 ||input_num%10 == 9 ){
            clap++;

        }
        //박수 출력
        if(clap==1){
            System.out.println("박수짝");
        } else if (clap == 2) {
            System.out.println("박수짝짝");
        }
    }
}
