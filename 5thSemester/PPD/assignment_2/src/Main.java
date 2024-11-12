import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) {
        try {
            ProcessBuilder producerBuilder = new ProcessBuilder("java", "Producer");
            Process producerProcess = producerBuilder.start();

            ProcessBuilder consumerBuilder = new ProcessBuilder("java", "Consumer");
            Process consumerProcess = consumerBuilder.start();

            try (
                    InputStream producerOutput = producerProcess.getInputStream();
                    OutputStream consumerInput = consumerProcess.getOutputStream()
            ) {
                byte[] buffer = new byte[1024];
                int bytesRead;

                while ((bytesRead = producerOutput.read(buffer)) != -1) {
                    consumerInput.write(buffer, 0, bytesRead);
                    consumerInput.flush();
                }
            }

            consumerProcess.getOutputStream().close();

            BufferedReader reader = new BufferedReader(new InputStreamReader(consumerProcess.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            producerProcess.waitFor();
            consumerProcess.waitFor();

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}