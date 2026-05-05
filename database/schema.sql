CREATE DATABASE IF NOT EXISTS estufa_iot;

USE estufa_iot;

CREATE TABLE IF NOT EXISTS leituras (
  id INT AUTO_INCREMENT PRIMARY KEY,
  temperatura FLOAT,
  umidade FLOAT,
  luminosidade FLOAT,
  timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
);