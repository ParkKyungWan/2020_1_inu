import java.util.Scanner;
public class class0330_3 {
    public static void main(String args[]){

        Scanner sc = new Scanner(System.in);
        //수량 확인용 계산서
        int[][] bill = new int[4][2];
        int total=0;
        for(int i = 0 ; i <5; i++) {
            String order = sc.nextLine();
            int price=0;
            //예제 사용
            switch (order) {
                case "에스프레소":
                    price = 2000;
                    //주문 추가
                    bill[0][0]++;
                    break;
                case "카푸치노":

                case "카페라떼":
                    price = 3500;
                    if(order.equals("카푸치노")){
                        bill[1][0]++;
                    }else{
                        bill[2][0]++;
                    }
                    break;
                case "아메리카노":
                    price = 2500;
                    bill[3][0]++;
                    break;
            }
            //최종 가격에 해당 상품의 가격 추가
            total+=price;



        }
        //출력
        System.out.println("<계산서>");
        System.out.println("품명       단가  수량  금액");
        if(bill[3][0]>0)
            System.out.printf( "아메리카노  2500  %d   %d\n",bill[3][0],bill[0][0]*2500);
        if(bill[1][0]>0)
            System.out.printf( "카푸치노    3500  %d   %d\n",bill[1][0],bill[0][0]*3500);
        if(bill[0][0]>0)
            System.out.printf( "에스프레소  2000  %d   %d\n",bill[0][0],bill[0][0]*2000);
        if(bill[2][0]>0)
            System.out.printf( "카페라떼    3500  %d   %d\n",bill[2][0],bill[0][0]*3500);
        System.out.printf( "합계                  %d",total);
    }

}
