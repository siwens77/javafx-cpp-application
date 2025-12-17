import javafx.fxml.FXML;
import javafx.scene.control.Label;

public class GameOverController {

    @FXML
    private Label whoWonLabel;

    public void setWinner(String winner) {

        
        switch(winner){
            case "W":
                whoWonLabel.setText("GAME OVER\nYOU WON!");
                break;
            case "L":
                whoWonLabel.setText("GAME OVER\nYOU LOST!");
                break;
                case "C":
                    whoWonLabel.setText("GAME OVER\nPUSSY?");
                    break;
            default:
                break;
        }
    }
}