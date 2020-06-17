import java.util.InputMismatchException;
import java.util.Scanner;
public class class0330_2 {
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
        //입력받기전 변수 초기화
        int input_num = 128;

        //무한루프
        while(true){
            //입력시 예외처리
            try {
                input_num = sc.nextInt();
            }catch(InputMismatchException e){
                System.out.println("정수를 입력해 주셔야 합니다.");
                return;
            }
            //1~127일때
            if(input_num>=1 && input_num<=127){
                int i = 1;
                //별그리기-윗부분
                while(i<=input_num){
                    int j = 1;
                    while(j<=i){
                        System.out.print("*");
                        j++;
                    }
                    System.out.println("");
                    i++;
                }
                //별그리기-아랫부분
                input_num--;
                while(input_num>=1){
                    int j = 1;
                    while(j<=input_num){
                        System.out.print("*");
                        j++;
                    }
                    System.out.println("");
                    input_num--;
                }

            //0을 입력하면 종료
            }else if(input_num==0){
                return;
            //0 도 아니면 해당 문자열 출력
            }else{
                System.out.println("0~127까지만 입력해주세요.");
            }
        }
    }
}
