import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Tooltip;
import javafx.scene.Node;
import javafx.stage.Stage;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import javafx.scene.layout.AnchorPane;
import javafx.scene.media.AudioClip;
import javafx.scene.text.Text;
import java.net.URL;
import java.util.Collections;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.control.Tooltip;


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
    private Text heroPowerText;
    @FXML
    private Text heroSpeedText;
    @FXML
    private Text heroHealthText;
    @FXML
    private ImageView cat1View;
    @FXML
    private ImageView cat2View;
    @FXML
    private ImageView cat3View;
    @FXML
    private ImageView catHeroView;
    @FXML
    private Tooltip card1Tooltip;
    @FXML
    private Tooltip card2Tooltip;
    @FXML
    private Tooltip card3Tooltip;
    static {
        URL sound = Controller.class.getResource("resources/sounds/click.wav");
        click1 = new AudioClip(sound.toString());
    }

    @FXML
    private void initialize() {
        click1.setVolume(0);
        click1.play();
        click1.setVolume(1.0);
    }

    public void setMainWindow(Stage stage) {
        this.stage = stage;
    }

    public static void clearFiles() {
        String[] files = {
            "clickedCard.txt",
            "statistics.txt",
            "clickedCat.txt",
            "whosturn.txt",
            "gameover.txt",
            "cards.txt",
            "clickedCard.tmp",
            "clickedCat.tmp"
        };

        for (String filePath : files) {
            File file = new File(filePath);
            if (file.exists()) {
                boolean deleted = file.delete();
            }
        }
    }

    public void endGame(String whoWon) {
        clearFiles(); 
        if (gameProcess != null && gameProcess.isAlive()) {
            gameProcess.destroyForcibly();
        }
    
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("endGame.fxml"));
            Parent root = loader.load();
    
            GameOverController controller = loader.getController();
            controller.displayWinner(whoWon);
    
            Stage stage = (Stage) scenePane.getScene().getWindow();
            Scene scene = new Scene(root, 800, 578);
            stage.setScene(scene);
            stage.show();
    
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void updateStatistic(Controller controller){
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
                String line0 = br.readLine();
                String line1 = br.readLine();
                String line2 = br.readLine();
                String line3 = br.readLine();
                new PrintWriter(filePath).close();

                String[] words0 = line0.split(" ");
                String[] words1 = line1.split(" ");
                String[] words2 = line2.split(" ");
                String[] words3 = line3.split(" ");

                String health0 = words0.length > 0 ? words0[0] : "";
                String power0 = words0.length > 0 ? words0[1] : "";
                String speed0 = words0.length > 0 ? words0[2] : "";
                Platform.runLater(() -> {
                    controller.heroHealthText.setText("health: "+health0);
                    controller.heroSpeedText.setText("speed: "+speed0);
                    controller.heroPowerText.setText("power: "+power0);
                });
                String health1 = words1.length > 0 ? words1[0] : "";
                String power1 = words1.length > 0 ? words1[1] : "";
                String speed1 = words1.length > 0 ? words1[2] : "";
                Platform.runLater(() -> {
                    controller.healerHealthText.setText("health: "+health1);
                    controller.healerSpeedText.setText("speed: "+speed1);
                    controller.healerPowerText.setText("power: "+power1);
                });
                String health2 = words2.length > 0 ? words2[0] : "";
                String power2 = words2.length > 0 ? words2[1] : "";
                String speed2 = words2.length > 0 ? words2[2] : "";
                Platform.runLater(() -> {
                    controller.warriorHealthText.setText("health: "+health2);
                    controller.warriorSpeedText.setText("speed: "+speed2);
                    controller.warriorPowerText.setText("power: "+power2);
                });
                String health3 = words3.length > 0 ? words3[0] : "";
                String power3 = words3.length > 0 ? words3[1] : "";
                String speed3 = words3.length > 0 ? words3[2] : "";
                Platform.runLater(() -> {
                    controller.wizardHealthText.setText("health: "+health3);
                    controller.wizardSpeedText.setText("speed: "+speed3);
                    controller.wizardPowerText.setText("power: "+power3);
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
                String line1_1 = br.readLine();
                String line2 = br.readLine();
                String line2_2 = br.readLine();
                String line3 = br.readLine();
                String line3_3 = br.readLine();
                new PrintWriter(filePath).close();
                Platform.runLater(() -> {
                    controller.card1.setImage(new Image(getClass().getResource(line1).toExternalForm()));
                    controller.card1Tooltip.setText(line1_1);
                    controller.card2.setImage(new Image(getClass().getResource(line2).toExternalForm()));
                    controller.card2Tooltip.setText(line2_2);
                    controller.card3.setImage(new Image(getClass().getResource(line3).toExternalForm()));
                    controller.card3Tooltip.setText(line3_3);
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
        markPlayer(controller,true);
        updateStatistic(controller);
        updateCards(controller);
    }

    @FXML
    void closeB(ActionEvent e) throws IOException{
        click1.play();
        endGame("C");
    }

    @FXML
    void card1Click(ActionEvent e) {
        writeClickedCard("0");
    }

    @FXML
    void card2Click(ActionEvent e) {
    writeClickedCard("1");
    }

    @FXML
    void card3Click(ActionEvent e) {
    writeClickedCard("2");

    }

    private void writeClickedCard(String cardId) {
        try (FileWriter writer = new FileWriter("clickedCard.tmp")) {
            writer.write(cardId);
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void writeClickedCat(String catID) {
        try (FileWriter writer = new FileWriter("clickedCat.tmp")) {
            writer.write(catID);
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }
    
    void markPlayer(Controller controller, boolean first){
        new Thread(() -> {
            String filePath = "whosturn.txt";
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
                String line0 = br.readLine();
                new PrintWriter(filePath).close();
                Platform.runLater(() -> {
                    switch(line0){
                        case "hero":
                            controller.catHeroView.getStyleClass().add("card-frame");
                            controller.cat2View.getStyleClass().removeAll(Collections.singleton("card-frame"));
                            controller.cat3View.getStyleClass().removeAll(Collections.singleton("card-frame"));
                            controller.cat1View.getStyleClass().removeAll(Collections.singleton("card-frame"));
                            if(!first){updateCards(this);}
                            break;
                        case "healer":
                            controller.catHeroView.getStyleClass().removeAll(Collections.singleton("card-frame"));
                            controller.cat2View.getStyleClass().removeAll(Collections.singleton("card-frame"));
                            controller.cat3View.getStyleClass().removeAll(Collections.singleton("card-frame"));
                            controller.cat1View.getStyleClass().add("card-frame");
                            break;
                        case "warrior":
                            controller.catHeroView.getStyleClass().removeAll(Collections.singleton("card-frame"));
                            controller.cat3View.getStyleClass().removeAll(Collections.singleton("card-frame"));
                            controller.cat1View.getStyleClass().removeAll(Collections.singleton("card-frame"));
                            controller.cat2View.getStyleClass().add("card-frame");
                            break;
                        case "wizard":
                            controller.catHeroView.getStyleClass().removeAll(Collections.singleton("card-frame"));
                            controller.cat2View.getStyleClass().removeAll(Collections.singleton("card-frame"));
                            controller.cat1View.getStyleClass().removeAll(Collections.singleton("card-frame"));
                            controller.cat3View.getStyleClass().add("card-frame");
                            break;
                        default:
                            break;
                    }
                });

            } catch (IOException e) {
                e.printStackTrace();
            }
        }).start();
    }

    @FXML
    void cat1click(ActionEvent e){
        writeClickedCat("0");
    }
    @FXML
    void cat2click(ActionEvent e){
        writeClickedCat("1");
    }
    @FXML
    void cat3click(ActionEvent e){
        writeClickedCat("2");
    }

    @FXML
    void catHeroClick(ActionEvent e) {
        writeClickedCat("-1");
    }

    void sendClicks(){
        File tmpFile = new File("clickedCard.tmp");
        File txtFile = new File("clickedCard.txt");
        File tmpFile2 = new File("clickedCat.tmp");
        File txtFile2 = new File("clickedCat.txt");
        tmpFile.renameTo(txtFile);
        tmpFile2.renameTo(txtFile2);
    }

    void checkGameOver(){
        new Thread(() -> {
            String filePath = "gameover.txt";
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
                String line0 = br.readLine();
                new PrintWriter(filePath).close();
                Platform.runLater(() -> {
                    if ("W".equals(line0) || "L".equals(line0)){
                        endGame(line0);
                    }
                });

            } catch (IOException e) {
                e.printStackTrace();
            }
        }).start();
    }

    @FXML
    void nextTurn(ActionEvent e){
        updateStatistic(this);
        checkGameOver();
        markPlayer(this,false);
        sendClicks();
    }

}