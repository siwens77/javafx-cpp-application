public class Wizard extends Cat{
    public Wizard(int h, int s, int p){
        super(h, s, p);
    }
    @Override
    public String getHealthStatus() {
        return "wizard health: " + this.health;
    }
    
    @Override
    public String getSpeedStatus() {
        return "wizard speed: " + this.speed;
    }
    
    @Override
    public String getPowerStatus() {
        return "wizard power: " + this.power;
    }

}
