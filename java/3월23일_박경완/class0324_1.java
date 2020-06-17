public class class0324_1 {
    public static void main(String args[]){
        for (int i = 1; i <=9; i++){
            for(int j = 2; j <=9; j++){

                System.out.printf("%d * %d = %d",j,i,i*j);
                if(j==9){
                    System.out.print("\n");
                }else{
                    if(i*j>9){
                        System.out.print(", ");
                    }else{
                        System.out.print(",  ");
                    }
                }

            }
        }
    }
}

