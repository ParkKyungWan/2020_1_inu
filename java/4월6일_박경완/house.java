//4월 6일 과제_201901561박경완
public class house {
    String owner;
    long price;
    String adress;             //필드 3개 작성

    public house(){                     //생성자_1
        owner = "소유주 없음";          //필드초기화1
        price = 0;
        adress = "정해지지 않음";
        System.out.println("빈 집이 생성되었습니다.\n");
    }
    public house(String owner,long price,String adress){  //생성자_2
        this.owner = owner;                     //필드초기화2
        this.price = price;
        this.adress = adress;
        System.out.printf("생성된 집의\n주인: %s\n가격: %d\n주소: %s\n\n",owner,price,adress);
    }
    public void holder_change(String owner){   //소유주 변경 메소드
        System.out.printf("소유주가 %s 님으로 변경되었습니다.\n\n",owner);
        this.owner = owner;         //this 레퍼런스 사용
    }
    public void price_fluctuations(long amount){ //가격 변동 메소드

        System.out.printf("가격변동 : %d",price);
        price +=amount;
        System.out.printf(" -> %d\n\n",price);
    }
    public void reset(String owner,long price,String adress){ //정보 재설정
        this.owner = owner;
        this.price = price;
        this.adress = adress;
        System.out.printf("수정된 집의\n주인: %s\n가격: %d\n주소: %s\n\n",owner,price,adress);
    }

    public static void main(String args[]){

        System.out.println("//house 1 FreeHouse (생성자 1)");
        house FreeHouse = new house();   //빈 집

        System.out.println("//house 2 MyHouse (생성자 2)");
        house MyHouse = new house("박경완",3000000000L,"아트센터대로97번길");
        //우리집


        System.out.println("//메소드 - 소유주 변경_MyHouse");
        MyHouse.holder_change("홍길동"); //홍길동이 우리집 구매


        System.out.println("//메소드 - 가격 변동_MyHouse");
        MyHouse.price_fluctuations(-30000000); //가격 폭락


        System.out.println("//메소드 - 정보_재설정_FreeHouse ");
        MyHouse.reset("박경완",600000000000L,"한강 근처"); //가격 폭락



    }
}
