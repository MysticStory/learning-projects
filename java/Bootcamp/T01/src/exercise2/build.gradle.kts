plugins {
    id("java")
    id("application")
}

application {
    mainClass.set("com.example.Main")
}

tasks.run.configure {
    standardInput = System.`in`
}

group = "com.example"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

dependencies {
    testImplementation(platform("org.junit:junit-bom:5.10.0"))
    testImplementation("org.junit.jupiter:junit-jupiter")
}

tasks.test {
    useJUnitPlatform()
}