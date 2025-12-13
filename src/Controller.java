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
import javafx.scene.text.Text;
import java.net.URL;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;




public class Controller {

    private Stage stage; 
    private Scene scene; 
    private static Process gameProcess;
    private static AudioClip click1;
    @FXML
    private AnchorPane scenePane; 
    @FXML
    private ImageView card1;
    @FXML
    private ImageView card2;
    @FXML
    private ImageView card3;
    @FXML
    private Text healerPowerText;
    @FXML
    private Text healerSpeedText;
    @FXML
    private Text healerHealthText;
    @FXML
    private Text warriorPowerText;
    @FXML
    private Text warriorSpeedText;
    @FXML
    private Text warriorHealthText;
    @FXML
    private Text wizardPowerText;
    @FXML
    private Text wizardSpeedText;
    @FXML
    private Text wizardHealthText;

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

    void updateStatistic(Controller controller){
        new Thread(() -> {
            String filePath = "statistics.txt";
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
                String line0 = br.readLine();//TODO: set somewhere hero health etc


                String line1 = br.readLine();
                String[] words = line1.split(" ");
                String health = words.length > 0 ? words[0] : "";
                String power = words.length > 0 ? words[1] : "";
                String speed = words.length > 0 ? words[2] : "";
                Platform.runLater(() -> {
                    controller.healerHealthText.setText(health);
                    controller.healerSpeedText.setText(speed);
                    controller.healerPowerText.setText(power);
                });
                String line2 = br.readLine();
                String[] words2 = line2.split(" ");
                String health2 = words2.length > 0 ? words2[0] : "";
                String power2 = words2.length > 0 ? words2[1] : "";
                String speed2 = words2.length > 0 ? words2[2] : "";
                Platform.runLater(() -> {
                    controller.warriorHealthText.setText(health2);
                    controller.warriorSpeedText.setText(speed2);
                    controller.warriorPowerText.setText(power2);
                });
                String line3 = br.readLine();
                String[] words3 = line3.split(" ");
                String health3 = words3.length > 0 ? words3[0] : "";
                String power3 = words3.length > 0 ? words3[1] : "";
                String speed3 = words3.length > 0 ? words3[2] : "";
                Platform.runLater(() -> {
                    controller.wizardHealthText.setText(health3);
                    controller.wizardSpeedText.setText(speed3);
                    controller.wizardPowerText.setText(power3);
                });


            } catch (IOException e) {
                e.printStackTrace();
            }
        }).start();
    }

    void updateCards(Controller controller){
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


            } catch (IOException e) {
                e.printStackTrace();
            }
        }).start();
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
        gameProcess = pb.start();
        updateStatistic(controller);
        updateCards(controller);
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

    @FXML
    void card1Click(ActionEvent e ) throws IOException{
        System.out.println("clicked 1");
    }
    @FXML
    void card2Click(ActionEvent e ) throws IOException{
        System.out.println("clicked 2");
    }
    @FXML
    void card3Click(ActionEvent e ) throws IOException{
        System.out.println("clicked 3");
    }
}


