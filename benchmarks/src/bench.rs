static mut A: [[f32;1050]; 1050] = [[0.0; 1050];1050];
static mut B: [[f32;1050]; 1050] = [[0.0; 1050];1050];
static mut C: [[f32;1050]; 1050] = [[0.0; 1050];1050];

fn mat_mult()
{
    unsafe {
    for i in 0..1050
    {
        for j in 0..1050
        {
            for k in 0..1050
            {
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }
    }
}


fn main()
{
    unsafe{
    for i in 0..1050
    {
        for j in 0..1050
        {
            A[i][j] = 1.5;
            B[i][j] = 2.5;
        }
    }

    mat_mult();

    println!("{} {} {}", C[0][0], C[525][525], C[1049][1049]);
    }
}
