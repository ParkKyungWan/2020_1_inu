import java.util.StringTokenizer;

public class class0511_1 {
    public static void main(String args[]){

        StringTokenizer st = new StringTokenizer("냉장고,세탁기,에어컨,TV,오디오",",");
        //토큰을 가지고 있을때 까지 ( 전부 출력하기 전까지 )
        while(st.hasMoreTokens())
            //다음 토큰 출력
            System.out.println(st.nextToken());
    }



}
