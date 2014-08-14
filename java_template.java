
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.io.InputStream;
import java.util.StringTokenizer;

public class Main {

	public void solve() {

	}

	public void run() {
		tokenizer = null;
		reader = new BufferedReader(new InputStreamReader(System.in));
		out = new PrintWriter(System.out);

		solve();

		out.close();
	}

	public static void main(String[] args) {
		new Main().run();
	}

	public StringTokenizer tokenizer;
	public BufferedReader reader;
	public PrintWriter out;

	public String next() {
		while (tokenizer == null || !tokenizer.hasMoreTokens()) {
			try {
				tokenizer = new StringTokenizer(reader.readLine());
			}
			catch (IOException e) {
				throw new RuntimeException(e);
			}
		}
		return tokenizer.nextToken();
	}

	public int nextInt() {
		return Integer.parseInt(next());
	}

}
