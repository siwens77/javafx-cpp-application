import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.scene.text.Font;
import javafx.scene.image.Image;

public class Main extends Application {
    @Override
    public void start(Stage primaryStage) throws Exception {
        Font.loadFont(getClass().getResource("/resources/fonts/font.otf").toExternalForm(), 16);
        FXMLLoader loader = new FXMLLoader(getClass().getResource("/mainscene.fxml"));
        Parent root = loader.load();
        Controller controller = loader.getController();


        Image image = new Image("/resources/images/icon.png");
        primaryStage.getIcons().add(image);

        controller.setMainWindow(primaryStage);
        primaryStage.setTitle("Cats Battle");
        primaryStage.setScene(new Scene(root, 800,578));
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}