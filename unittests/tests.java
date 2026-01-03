import org.junit.Test;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

public class tests {

    @Test
    public void testHealer() {
        Healer h = new Healer(80, 60, 10);
        assertEquals("healer health: 80", h.getHealthStatus());
        assertEquals("healer speed: 60", h.getSpeedStatus());
        assertEquals("healer power: 10", h.getPowerStatus());
    }
    @Test
    public void testWizard() {
        Wizard z = new Wizard(70, 40, 90);
        assertEquals("wizard health: 70", z.getHealthStatus());
        assertEquals("wizard speed: 40", z.getSpeedStatus());
        assertEquals("wizard power: 90", z.getPowerStatus());
    }
    @Test
    public void testHero() {
        Hero hero = new Hero(120, 55, 35);
        assertEquals("hero health: 120", hero.getHealthStatus());
        assertEquals("hero speed: 55", hero.getSpeedStatus());
        assertEquals("hero power: 35", hero.getPowerStatus());
    }
    @Test
    public void testWarrior() {
        Warrior w = new Warrior(100, 50, 20);
        assertEquals("warrior health: 100", w.getHealthStatus());
        assertEquals("warrior speed: 50", w.getSpeedStatus());
        assertEquals("warrior power: 20", w.getPowerStatus());
    }

    @Test
    public void testPolymorphism() {
        Warrior w = new Warrior(10, 10, 10);
        assertTrue("Warrior should be Cat", w instanceof Cat);
    }
    @Test
    public void testWarriorAndHealerComparison() {
        Warrior w = new Warrior(100, 50, 20);
        Healer h = new Healer(100, 50, 20);

        assertEquals("warrior health: 100", w.getHealthStatus());
        assertEquals("healer health: 100", h.getHealthStatus());
        assertNotEquals(w.getHealthStatus(), h.getHealthStatus());
    }

    @Test
    public void testSetStatistics() {
        Hero hero = new Hero(10, 10, 10);
        hero.setStatistics(200, 150, 500);

        assertEquals("hero health: 200", hero.getHealthStatus());
        assertEquals("hero speed: 150", hero.getSpeedStatus());
        assertEquals("hero power: 500", hero.getPowerStatus());
    }

    @Test
    public void testCatTypeEnum() {
        assertNotNull(CatType.HERO);
        assertNotNull(CatType.HEALER);
        assertNotNull(CatType.WARRIOR);
        assertNotNull(CatType.WIZARD);

        assertEquals(CatType.HERO, CatType.valueOf("HERO"));
    }
    
}
