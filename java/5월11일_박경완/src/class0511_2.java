import java.util.Scanner;
import java.util.StringTokenizer;

public class class0511_2 {
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
        StringTokenizer st = new StringTokenizer(sc.next(),"+" );
        // + 를 기준으로 토큰을 나눕니다.
        int answer = Integer.parseInt(st.nextToken());
        //answer 에 토큰이 하나하나 쌓이며 더해집니다
        while(st.hasMoreTokens()){
            answer += Integer.parseInt(st.nextToken());
        }
        System.out.println(answer);

    }
}
