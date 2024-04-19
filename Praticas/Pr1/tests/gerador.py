# -*- encoding: utf-8 -*-

# Online Python - IDE, Editor, Compiler, Interpreter
import random

def random_name():
    names = ['Alice', 'Miguel', 'Sophia', 'Arthur', 'Helena', 'Bernardo', 'Valentina', 'Heitor', 'Laura', 'Davi', 'Isabella', 'Lorenzo', 'Manuela', 'Theo', 'Julia', 'Pedro', 'Heloisa', 'Gabriel', 'Luiza', 'Enzo', 'MariaLuiza', 'Matheus', 'Lorena', 'Lucas', 'Livia', 'Benjamin', 'Giovanna', 'Nicolas', 'MariaEduarda', 'Guilherme', 'Beatriz', 'Rafael', 'MariaClara', 'Joaquim', 'Cecilia', 'Samuel', 'Eloa', 'EnzoGabriel', 'Lara', 'JoaoMiguel', 'MariaJulia', 'Henrique', 'Isadora', 'Gustavo', 'Mariana', 'Murilo', 'Emanuelly', 'PedroHenrique', 'AnaJulia', 'Pietro', 'AnaLuiza', 'Lucca', 'AnaClara', 'Felipe', 'Melissa', 'JoaoPedro', 'Yasmin', 'Isaac', 'MariaAlice', 'Benicio', 'Isabelly', 'Daniel', 'Lavinia', 'Anthony', 'Esther', 'Leonardo', 'Sarah', 'DaviLucca', 'Elisa', 'Bryan', 'Antonella', 'Eduardo', 'Rafaela', 'JoaoLucas', 'MariaCecilia', 'Victor', 'Liz', 'Joao', 'Marina', 'Caua', 'Nicole', 'Antonio', 'Maitê', 'Vicente', 'Isis', 'Caleb', 'Alicia', 'Gael', 'Luna', 'Bento', 'Rebeca', 'Caio', 'Agatha', 'Emanuel', 'Leticia', 'Vinicius', 'Maria', 'JoaoGuilherme', 'Gabriela', 'DaviLucas', 'AnaLaura', 'Noah', 'Catarina', 'JoaoGabriel', 'Clara', 'JoaoVictor', 'AnaBeatriz', 'LuizMiguel', 'Vitoria', 'Francisco', 'Olivia', 'Kaique', 'MariaFernanda', 'Otavio', 'Emilly', 'Augusto', 'MariaValentina', 'Levi', 'Milena', 'Yuri', 'MariaHelena', 'Enrico', 'Bianca', 'Thiago', 'Larissa', 'Ian', 'Mirella', 'VictorHugo', 'MariaFlor', 'Thomas', 'Allana', 'Henry', 'AnaSophia', 'LuizFelipe', 'Clarice', 'Ryan', 'Pietra', 'ArthurMiguel', 'MariaVitoria', 'DaviLuiz', 'Maya', 'Nathan', 'Lais', 'PedroLucas', 'Ayla', 'DaviMiguel', 'AnaLivia', 'Raul', 'Eduarda', 'PedroMiguel', 'Mariah', 'LuizHenrique', 'Stella', 'Luan', 'Ana', 'Erick', 'Gabrielly', 'Martin', 'Sophie', 'Bruno', 'Carolina', 'Rodrigo', 'MariaLaura', 'LuizGustavo', 'MariaHeloisa', 'ArthurGabriel', 'MariaSophia', 'Breno', 'Fernanda', 'Kauê', 'Malu', 'EnzoMiguel', 'Analu', 'Fernando', 'Amanda', 'ArthurHenrique', 'Aurora', 'LuizOtavio', 'MariaIsis', 'CarlosEduardo', 'Louise', 'Tomas', 'Heloise', 'LucasGabriel', 'AnaVitoria', 'Andre', 'AnaCecilia', 'Jose', 'AnaLiz', 'Yago', 'Joana', 'Danilo', 'Luana', 'Anthony', 'Gabriel', 'Antonia', 'Ruan', 'Isabel', 'Miguel', 'Henrique', 'Bruna', 'Oliver']
    return names[random.randint(0, len(names)-1)]

def random_course():
    course = ['direito', 'computacao', 'nutricao']
    return course[random.randint(0, len(course)-1)]

for i in range(500):
    print(f'{random_name()} {random_course()} {random.random() * 10:.1f}')
