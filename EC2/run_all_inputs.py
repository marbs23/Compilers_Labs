import os
import subprocess
 
# Archivos c++
programa = ["main.cpp", "scanner.cpp", "token.cpp","parser.cpp","ast.cpp"]

# Compilar
compile = ["g++"] + programa
print("Compilando:", " ".join(compile))
result = subprocess.run(compile, capture_output=True, text=True)

if result.returncode != 0:
    print("Error en compilación:\n", result.stderr)
    exit(1)

print("Compilación exitosa")

# Ejecutar
input_dir = "inputs"
for i in range(1, 12): 
    filename = f"input{i}.txt"
    filepath = os.path.join(input_dir, filename)
    if os.path.isfile(filepath):
        print(f"Ejecutando {filename}")
        run_cmd = ["./a.out", filepath]
        subprocess.run(run_cmd, capture_output=True, text=True)

        # Si el programa genera ast.dot, convertirlo a imagen en inputs/
        if os.path.isfile("ast.dot"):
            output_img = os.path.join(input_dir, f"ast_{i}.png")
            dot_cmd = ["dot", "-Tpng", "ast.dot", "-o", output_img]
            print(f"Generando {output_img}")
            subprocess.run(dot_cmd, capture_output=True, text=True)
    else:
        print(filename, "no encontrado en", input_dir)