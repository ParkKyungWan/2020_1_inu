public class class0324_2 {
    public static void main(String args[]){
        int i;
        int j=2;
        while(j<=9){
            i=1;
            while(i<=9){

                System.out.printf("%d * %d = %d",j,i,i*j);
                if(i==9){
                    System.out.print("\n");
                }else{
                    if(i*j>9){
                        System.out.print(", ");
                    }else{
                        System.out.print(",  ");
                    }
                }
                i++;
            }
            j++;
        }
    }
}

