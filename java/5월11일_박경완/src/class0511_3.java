import java.util.Scanner;
import java.util.StringTokenizer;

public class class0511_3 {
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
        StringTokenizer st = new StringTokenizer(sc.next(),"+-", true );
        //+ 혹은 - 를 기준으로 토큰을 나누며, +혹은 -또한 토큰에 포함됩니다.
        int answer = Integer.parseInt(st.nextToken());
        //첫번째 토큰을 answer 에 담고, 뒤따라 오는 토큰이 + 인지 -인지에 따라 그 다음 토큰을 합할 것 인지
        //뺄 것 인지의 여부를 결정하여 연산합니다.
        while(st.hasMoreTokens()){
            if (st.nextToken().equals("+"))
                answer += Integer.parseInt(st.nextToken());
            else
                answer -= Integer.parseInt(st.nextToken());
        }
        System.out.println(answer);

    }
}
