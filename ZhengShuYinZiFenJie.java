import java.util.Scanner;

public class ZhengShuYinZiFenJie {

    private static int total=0;

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n;

        while(true){
            //��ԭ��ʼֵ
            total = 0;
            n = input.nextInt();//����nֵ

            recursive(n); //�ݹ����

            System.out.println(total);
            System.out.println("-------------");

        }
    }

    private static void recursive(int n){
        if(n == 1)
            total++;
        else
            for(int i=2; i<=n; i++)
                if(n%i == 0)
                    recursive(n/i);

    }
}
