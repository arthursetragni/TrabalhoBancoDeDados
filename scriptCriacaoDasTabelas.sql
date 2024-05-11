CREATE TABLE Ambulatorio (
    numeroA INT PRIMARY KEY,
    andar INT NOT NULL,
    capacidade INT NOT NULL
);
CREATE TABLE Consulta (
    CRM INT,
    RG INT,
    data DATE NOT NULL,
    hora TIME NOT NULL,
    PRIMARY KEY (CRM, RG),
    FOREIGN KEY (CRM) REFERENCES Medico(CRM),
    FOREIGN KEY (RG) REFERENCES Paciente(RG)
);
CREATE TABLE Funcionario (
    RG INT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    idade INT NOT NULL,
    cidade VARCHAR(100) NOT NULL,
    salario DECIMAL(10,2) NOT NULL
);
CREATE TABLE Medico (
    CRM INT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    idade INT NOT NULL,
    cidade VARCHAR(100) NOT NULL,
    especialidade VARCHAR(100) NOT NULL,
    numeroA INT,
    FOREIGN KEY (numeroA) REFERENCES Ambulatorio(numeroA)
);
CREATE TABLE Paciente (
    RG INT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    idade INT NOT NULL,
    cidade VARCHAR(100) NOT NULL,
    doenca VARCHAR(100) NOT NULL
);


