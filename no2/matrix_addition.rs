use std::io;

fn main() {
    // 행렬의 크기 입력
    let mut input = String::new();
    println!("Enter the number of rows and columns for the matrices:");
    io::stdin()
        .read_line(&mut input)
        .expect("Failed to read input");
    
    let dims: Vec<usize> = input
        .trim()
        .split_whitespace()
        .map(|x| x.parse().expect("Invalid number"))
        .collect();

    if dims.len() != 2 {
        eprintln!("Please provide exactly two numbers (rows and columns).");
        return;
    }

    let rows = dims[0];
    let cols = dims[1];

    // 첫 번째 행렬 입력
    println!("Enter the elements of the first matrix (row by row):");
    let matrix_a = read_matrix(rows, cols);

    // 두 번째 행렬 입력
    println!("Enter the elements of the second matrix (row by row):");
    let matrix_b = read_matrix(rows, cols);

    // 행렬 덧셈
    let result_matrix = add_matrices(&matrix_a, &matrix_b, rows, cols);

    // 결과 출력
    println!("Resultant Matrix:");
    print_matrix(&result_matrix, rows, cols);
}

// 행렬 입력 함수
fn read_matrix(rows: usize, cols: usize) -> Vec<Vec<i32>> {
    let mut matrix = Vec::new(); // 행렬 저장용 벡터

    for i in 0..rows {
        println!("Enter row {} (space-separated):", i + 1);
        let mut input = String::new();
        io::stdin()
            .read_line(&mut input)
            .expect("Failed to read input");
        
        let row: Vec<i32> = input
            .trim()
            .split_whitespace()
            .map(|x| x.parse().expect("Invalid number"))
            .collect();

        if row.len() != cols {
            eprintln!("Expected {} elements for this row, got {}.", cols, row.len());
            std::process::exit(1);
        }

        matrix.push(row); // 행 추가
    }

    matrix
}

// 두 행렬의 합을 계산하는 함수
fn add_matrices(
    matrix_a: &Vec<Vec<i32>>,
    matrix_b: &Vec<Vec<i32>>,
    rows: usize,
    cols: usize,
) -> Vec<Vec<i32>> {
    let mut result = Vec::new(); // 결과 행렬 저장용 벡터

    for i in 0..rows {
        let mut row = Vec::new();
        for j in 0..cols {
            row.push(matrix_a[i][j] + matrix_b[i][j]); // 요소별 합 계산
        }
        result.push(row); // 결과 행 추가
    }

    result
}

// 행렬 출력 함수
fn print_matrix(matrix: &Vec<Vec<i32>>, rows: usize, cols: usize) {
    for i in 0..rows {
        for j in 0..cols {
            print!("{} ", matrix[i][j]);
        }
        println!(); // 행 끝에 줄바꿈
    }
}