import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.Node;
import javafx.stage.Stage;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import javafx.scene.layout.AnchorPane;
import javafx.scene.media.AudioClip;
import java.net.URL;

import javafx.scene.image.Image;
import javafx.scene.image.ImageView;




public class Controller {

    private Stage stage; 
    private Scene scene; 
    private static Process gameProcess;
    @FXML
    private AnchorPane scenePane; 
    private static AudioClip click1;
    @FXML
    private ImageView card1;
    @FXML
    private ImageView card2;
    @FXML
    private ImageView card3;

    @FXML
    private void initialize() {
        click1.setVolume(0);
        click1.play();
        click1.setVolume(1.0);
    }


    public void setMainWindow(Stage stage) {
        this.stage = stage;
    }

    static {
        URL sound = Controller.class.getResource("resources/sounds/click.wav");
        click1 = new AudioClip(sound.toString());
    }

    @FXML
    void PlayB(ActionEvent event) throws IOException {
        
        click1.play();
        
        FXMLLoader loader = new FXMLLoader(getClass().getResource("racescene.fxml"));
        Parent root = loader.load();
        Controller controller = loader.getController();

        stage = (Stage)((Node)event.getSource()).getScene().getWindow();
        scene = new Scene(root, 800, 578);
        stage.setScene(scene);
        stage.show();
    

        String exePath = new File("game").getAbsolutePath();
        ProcessBuilder pb = new ProcessBuilder(exePath);
        pb.inheritIO();


        new Thread(() -> {
            String filePath = "cards.txt";
            File file = new File(filePath);
            while (!file.exists() || file.length() == 0) {
                try {
                    Thread.sleep(100); 
                } catch (InterruptedException e) {
                    e.printStackTrace();
                    return;
                }
            }
    
            try (BufferedReader br = new BufferedReader(new FileReader(file))) {
                String line1 = br.readLine();
                String line2 = br.readLine();
                String line3 = br.readLine();
                Platform.runLater(() -> {
                    controller.card1.setImage(new Image(getClass().getResource(line1).toExternalForm()));
                    controller.card2.setImage(new Image(getClass().getResource(line2).toExternalForm()));
                    controller.card3.setImage(new Image(getClass().getResource(line3).toExternalForm()));
                });

                System.out.println("path to file1" + line1);
                System.out.println("path to file2" + line2);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }).start();
        gameProcess = pb.start();
    }
    @FXML
    void closeB(ActionEvent e) throws IOException{
        click1.play();
        if (gameProcess != null && gameProcess.isAlive()) {
            gameProcess.destroyForcibly();
        }
        stage = (Stage)scenePane.getScene().getWindow();
        stage.close();
    }
}


