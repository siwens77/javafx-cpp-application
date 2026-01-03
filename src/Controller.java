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
import javafx.scene.layout.AnchorPane;
import javafx.scene.media.AudioClip;
import javafx.scene.text.Text;
import java.net.URL;
import java.util.Arrays;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.control.Label;
import javafx.scene.control.Button;

public class Controller {

    private Cat heroCat;
    private Cat healerCat;
    private Cat warriorCat;
    private Cat wizardCat;
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
    @FXML
    private Label rulesLabel;
    @FXML
    private Button closeButton;
    @FXML
    private Label endLabel;
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
            //"clickedCard.tmp",
            //"clickedCat.tmp"
        };

        for (String filePath : files) {
            File file = new File(filePath);
            if(!file.delete()){
                System.err.println("FILE FAILED TO BE DELETED: "+ filePath);
            }
        }
    }

    public void endGame(String whoWon) {
        clearFiles(); 
        if (gameProcess != null && gameProcess.isAlive()) {
            gameProcess.destroyForcibly();
        }
        switch(whoWon){
            case "W":
                endLabel.setText("GAME OVER\nYOU WON!");
                break;
            case "L":
                endLabel.setText("GAME OVER\nYOU LOST!");
                break;
            default:
                break;
        }
        scenePane.setVisible(false);
        endLabel.setVisible(true);
    }

    public void updateStatistic(Controller controller){
        new Thread(() -> {
            String filePath = "statistics.txt";
            File file = new File(filePath);
            while (!file.exists() || file.length() == 0) {
                try {
                    Thread.sleep(100); 
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    System.err.println("ERROR IN PUTTING THREAD TO SLEEP!(STATISTICS.TXT)");
                    return;
                }
            }
    
            try (BufferedReader br = new BufferedReader(new FileReader(file))) {
                String line0 = br.readLine();
                String line1 = br.readLine();
                String line2 = br.readLine();
                String line3 = br.readLine();
                if (line0 == null || line1 == null || line2 == null || line3 == null) {
                    System.err.println("STATISTICS.TXT IS NOT LONG ENOUGH");
                    return;
                }
                try (FileWriter fw = new FileWriter(file, false)) {
                } catch (IOException e) {
                    System.err.println("FAILED TO CLEAR STATISTICS.TXT");
                    e.printStackTrace();
                    return;
                }

                String[] words0 = line0.split(" ");
                String[] words1 = line1.split(" ");
                String[] words2 = line2.split(" ");
                String[] words3 = line3.split(" ");

                Platform.runLater(() -> {
                    controller.heroCat.setStatistics(Integer.parseInt(words0[0]), Integer.parseInt(words0[2]), Integer.parseInt(words0[1]));
                    
                    controller.heroHealthText.setText(
                        String.join(" ", Arrays.copyOfRange(controller.heroCat.getHealthStatus().split(" "), 1, 3)));
                    controller.heroSpeedText.setText(
                        String.join(" ", Arrays.copyOfRange(controller.heroCat.getSpeedStatus().split(" "), 1, 3)));
                    controller.heroPowerText.setText(
                        String.join(" ", Arrays.copyOfRange(controller.heroCat.getPowerStatus().split(" "), 1, 3)));

                    controller.healerCat.setStatistics(Integer.parseInt(words1[0]), Integer.parseInt(words1[2]), Integer.parseInt(words1[1]));
                    
                    controller.healerHealthText.setText(
                        String.join(" ", Arrays.copyOfRange(controller.healerCat.getHealthStatus().split(" "), 1, 3)));
                    controller.healerSpeedText.setText(
                        String.join(" ", Arrays.copyOfRange(controller.healerCat.getSpeedStatus().split(" "), 1, 3)));
                    controller.healerPowerText.setText(
                        String.join(" ", Arrays.copyOfRange(controller.healerCat.getPowerStatus().split(" "), 1, 3)));

                    controller.warriorCat.setStatistics(Integer.parseInt(words2[0]), Integer.parseInt(words2[2]), Integer.parseInt(words2[1]));
                    
                    controller.warriorHealthText.setText(
                        String.join(" ", Arrays.copyOfRange(controller.warriorCat.getHealthStatus().split(" "), 1, 3)));
                    controller.warriorSpeedText.setText(
                        String.join(" ", Arrays.copyOfRange(controller.warriorCat.getSpeedStatus().split(" "), 1, 3)));
                    controller.warriorPowerText.setText(
                        String.join(" ", Arrays.copyOfRange(controller.warriorCat.getPowerStatus().split(" "), 1, 3)));

                    controller.wizardCat.setStatistics(Integer.parseInt(words3[0]), Integer.parseInt(words3[2]), Integer.parseInt(words3[1]));
                    
                    controller.wizardHealthText.setText(
                        String.join(" ", Arrays.copyOfRange(controller.wizardCat.getHealthStatus().split(" "), 1, 3)));
                    controller.wizardSpeedText.setText(
                        String.join(" ", Arrays.copyOfRange(controller.wizardCat.getSpeedStatus().split(" "), 1, 3)));
                    controller.wizardPowerText.setText(
                        String.join(" ", Arrays.copyOfRange(controller.wizardCat.getPowerStatus().split(" "), 1, 3)));
                });


            } catch (IOException e) {
                System.err.println("ERROR IN READING STATISTICS.TXT");
                e.printStackTrace();
                return;
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
                    Thread.currentThread().interrupt();
                    System.err.println("ERROR IN PUTTING THREAD TO SLEEP! (CARDS.TXT)");
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
                try (FileWriter fw = new FileWriter(file, false)) {
                } catch (IOException e) {
                    System.err.println("FAILED TO CLEAR CARDS.TXT");
                    e.printStackTrace();
                    return;
                }
                Platform.runLater(() -> {
                    controller.card1.setImage(new Image(getClass().getResource(line1).toExternalForm()));
                    controller.card1Tooltip.setText(line1_1);
                    controller.card2.setImage(new Image(getClass().getResource(line2).toExternalForm()));
                    controller.card2Tooltip.setText(line2_2);
                    controller.card3.setImage(new Image(getClass().getResource(line3).toExternalForm()));
                    controller.card3Tooltip.setText(line3_3);
                });


            } catch (IOException e) {
                System.err.println("ERROR IN READING CARDS.TXT");
                e.printStackTrace();
                return;
            }
        }).start();
    }

    @FXML
    void PlayB(ActionEvent event) {
        try{
            click1.play();
            FXMLLoader loader = new FXMLLoader(getClass().getResource("rules.fxml"));
            Parent root = loader.load();
            Controller controller = loader.getController();

            stage = (Stage)((Node)event.getSource()).getScene().getWindow();
            scene = new Scene(root, 800, 578);
            stage.setScene(scene);
            stage.show();
        }catch (IOException e){
            System.err.println("FAILED TO LOAD RULES SCENE");
            e.printStackTrace();
        }

    }

    @FXML
    void PlayB2(ActionEvent event){
        try{
            click1.play();
            
            FXMLLoader loader = new FXMLLoader(getClass().getResource("racescene.fxml"));
            Parent root = loader.load();
            Controller controller = loader.getController();
            controller.heroCat = new Hero(0, 0, 0);       
            controller.healerCat = new Healer(0, 0, 0);   
            controller.warriorCat = new Warrior(0, 0, 0); 
            controller.wizardCat = new Wizard(0, 0, 0);

            stage = (Stage)((Node)event.getSource()).getScene().getWindow();
            scene = new Scene(root, 800, 578);
            stage.setScene(scene);
            stage.show();
        

            File exePath = new File("bin/CatsBattle");
            if (!exePath.exists()) {
                throw new IOException("C++ COMPILED FILE NOT FOUND: " + exePath.getAbsolutePath());
            }
            ProcessBuilder pb = new ProcessBuilder(exePath.getAbsolutePath());
            gameProcess = pb.start();
            markPlayer(controller,true);
            updateStatistic(controller);
            updateCards(controller);
        }catch(IOException e){
            System.err.println("FAILED TO LOAD FIGHTING SCENE");
            e.printStackTrace();
        }
    }

    @FXML
    void closeB(ActionEvent e) {
        clearFiles();
        click1.play();
        if (gameProcess != null && gameProcess.isAlive()) {
            gameProcess.destroyForcibly();
        }
        Platform.exit();
        System.exit(0);
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
            System.err.println("FAILED TO WRITE WHICH CARD WAS CLICKED");
            ex.printStackTrace();
        }
    }

    private void writeClickedCat(String catID) {
        try (FileWriter writer = new FileWriter("clickedCat.tmp")) {
            writer.write(catID);
        } catch (IOException ex) {
            System.err.println("FAILED TO WRITE WHICH CAT WAS CLICKED");
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
                    Thread.currentThread().interrupt();
                    System.err.println("ERROR IN PUTTING THREAD TO SLEEP!(WHOSTURN.TXT)");
                    return;
                }
            }
            try (BufferedReader br = new BufferedReader(new FileReader(file))) {
                String line0 = br.readLine();
                try (FileWriter fw = new FileWriter(file, false)) {
                } catch (IOException e) {
                    System.err.println("FAILED TO CLEAR WHOSETURN.TXT");
                    e.printStackTrace();
                    return;
                }
                Platform.runLater(() -> {
                    try{
                        CatType turn = CatType.valueOf(line0.toUpperCase());
                        controller.removeStyleFromAll("card-frame", 
                        controller.catHeroView, 
                        controller.cat1View, 
                        controller.cat2View, 
                        controller.cat3View);
                        switch(turn){
                            case HERO:
                                controller.catHeroView.getStyleClass().add("card-frame");
                                if(!first){updateCards(controller);}
                                break;
                            case HEALER:
                                controller.cat1View.getStyleClass().add("card-frame");
                                break;
                            case WARRIOR:
                                controller.cat2View.getStyleClass().add("card-frame");
                                break;
                            case WIZARD:
                                controller.cat3View.getStyleClass().add("card-frame");
                                break;
                            }
                        } catch (IllegalArgumentException e) {
                            System.err.println("INVALID TYPE OF CAT IN WHOSETURN.TXT: " + line0);
                        }
                    });
                } catch (IOException e) {
                    System.err.println("ERROR IN READING WHOSETURN.TXT");
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
                    Thread.currentThread().interrupt();
                    System.err.println("ERROR IN PUTTING THREAD TO SLEEP!(GAMEOVER.TXT)");
                    return;
                }
            }
            try (BufferedReader br = new BufferedReader(new FileReader(file))) {
                String line0 = br.readLine();
                try (FileWriter fw = new FileWriter(file, false)) {
                } catch (IOException e) {
                    System.err.println("FAILED TO CLEAR GAMEOVER.TXT");
                    e.printStackTrace();
                    return;
                }
                Platform.runLater(() -> {
                    if ("W".equals(line0) || "L".equals(line0)){
                        endGame(line0);
                    }
                });

            } catch (IOException e) {
                System.err.println("ERROR IN READING WHOSETURN.TXT");
                e.printStackTrace();
                return;
            }
        }).start();
    }

    @SafeVarargs
    private final <T extends Node> void removeStyleFromAll(String styleName, T... nodes) {
        for (T node : nodes) {
            if (node != null) {
                node.getStyleClass().remove(styleName);
            }
        }
    }

    @FXML
    void nextTurn(ActionEvent e){
        updateStatistic(this);
        checkGameOver();
        markPlayer(this,false);
        sendClicks();
    }

}