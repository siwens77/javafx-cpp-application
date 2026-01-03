public class Hero extends Cat{
    public Hero(int h, int s, int p){
        super(h, s, p);
    }
    @Override
    public String getHealthStatus() {
        return "hero health: " + this.health;
    }
    
    @Override
    public String getSpeedStatus() {
        return "hero speed: " + this.speed;
    }
    
    @Override
    public String getPowerStatus() {
        return "hero power: " + this.power;
    }

}
