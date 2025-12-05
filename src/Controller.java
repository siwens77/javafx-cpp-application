import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.Node;
import javafx.stage.Stage;
import java.io.IOException;
import javafx.scene.layout.AnchorPane;
import javafx.scene.media.AudioClip;
import java.net.URL;




public class Controller {

    private Stage stage; 
    private Scene scene; 
    @FXML
    private AnchorPane scenePane; 
    private static AudioClip click1;

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
        
        Parent root = FXMLLoader.load(getClass().getResource("racescene.fxml"));
        stage = (Stage)((Node)event.getSource()).getScene().getWindow();
        scene = new Scene(root, 800,578);
        stage.setScene(scene);
        stage.show();
    }
    @FXML
    void closeB(ActionEvent e) throws IOException{
        click1.play();

        stage = (Stage)scenePane.getScene().getWindow();
        stage.close();
    }



    @FXML
    void FightB(ActionEvent event) throws IOException {
        
        click1.play();
        
        Parent root = FXMLLoader.load(getClass().getResource("fightscene.fxml"));
        stage = (Stage)((Node)event.getSource()).getScene().getWindow();
        scene = new Scene(root, 800,578);
        stage.setScene(scene);
        stage.show();
    }

}
