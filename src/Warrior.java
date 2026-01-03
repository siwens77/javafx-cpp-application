public class Warrior extends Cat{
    public Warrior(int h, int s, int p){
        super(h, s, p);
    }
    @Override
    public String getHealthStatus() {
        return "warrior health: " + this.health;
    }
    
    @Override
    public String getSpeedStatus() {
        return "warrior speed: " + this.speed;
    }
    
    @Override
    public String getPowerStatus() {
        return "warrior power: " + this.power;
    }

}
