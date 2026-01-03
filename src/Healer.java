public class Healer extends Cat{
    public Healer(int h, int s, int p){
        super(h, s, p);
    }
    @Override
    public String getHealthStatus() {
        return "healer health: " + this.health;
    }
    
    @Override
    public String getSpeedStatus() {
        return "healer speed: " + this.speed;
    }
    
    @Override
    public String getPowerStatus() {
        return "healer power: " + this.power;
    }

}