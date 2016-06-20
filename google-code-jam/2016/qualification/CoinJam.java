
import java.math.BigInteger;
import java.util.Scanner;
import java.util.*;

public class CoinJam {
	
	static Map<BigInteger, BigInteger> memo = new HashMap<>();
	
	public static void main(String... args) {
		Scanner scanner = new Scanner(System.in);
		int T = scanner.nextInt();
		BigInteger[] divisors = new BigInteger[11];
		for (int t = 0; t < T; t++) {
			int N = scanner.nextInt();
			int J = scanner.nextInt();
			
			int count = 0;
			
			final int maxVal = (1 << N-2) - 1;
			System.out.printf("Case #%d:\n", t+1);
			
			 			
			for (int n = 0; count < J && n <= maxVal; n++) {
				String middle = N > 2 ? pad(Integer.toBinaryString(n), N-2) : "";
				String number = "1" + middle + "1";
				
				boolean isPrime = false;
				for (int b = 2; b <= 10; b++) {
					BigInteger base = new BigInteger(number, b);
					
					if (base.isProbablePrime(20)) {
						isPrime = true;
						break;
					} 
					divisors[b] = findDivisor(base);
					if (divisors[b] == null) {
						isPrime = true;
						break;
					}
				}
				if (!isPrime) {
					System.out.printf("%s", number);
					for (int b = 2; b <= 10; b++) {
						System.out.printf(" %s", divisors[b].toString());
					}
					count++;
					System.out.println("");
				}
			}
		}
	}
	
	public static String pad(String str, int n) {
		int dif = n - str.length();
		StringBuilder builder = new StringBuilder();
		while (builder.length() < dif) 
			builder.append("0");
		builder.append(str);
		return builder.toString();
	}
	
	public static BigInteger findDivisor(BigInteger num) {
		BigInteger div = new BigInteger("2");
		while (div.compareTo(new BigInteger("1000000")) < 0) {
			if (num.remainder(div).equals(BigInteger.ZERO)) {
				return div;
			} 
			BigInteger nextDiv = memo.get(div);
			if (nextDiv == null) {
				nextDiv = div.nextProbablePrime();
				memo.put(div, nextDiv);
			}
			div = nextDiv;
		}
		return null;
	}
}