<?php
session_start();

include $_SERVER['DOCUMENT_ROOT']."/db_conn.php";

if (isset($_POST['username']) && isset($_POST['password'])) {
    function validate($data) {
        $data = trim($data);
        $data = stripslashes($data);
        $data = htmlspecialchars($data);
        return $data;
    }

    $username = validate($_POST['username']);
    $password = validate($_POST['password']);

    if (empty($username)) {
        header("Location: index.php?error=Username is required");
        exit();
    }
    else if (empty($password)) {
        header("Location: index.php?error=Password is required");
        exit();
    }
    else {
        $password = md5($password);

        $sqlUser = "SELECT * FROM users WHERE username='$username' AND password='$password'";
        $resultUser = mysqli_query($conn, $sqlUser);
        
        if (mysqli_num_rows($resultUser) === 1) {
            $rowUser = mysqli_fetch_assoc($resultUser);

            if ($rowUser['username'] === $username && $rowUser['password'] === $password && $rowUser['verified']) {
                $_SESSION['id'] = $rowUser['id'];
                $_SESSION['verified'] = $rowUser['verified'];
                header("Location: http://".$_SERVER['HTTP_HOST']."/dashboard");
                exit();
            }
            else if (!$rowUser['verified']) {
                header("Location: index.php?error=Not yet verified! Please check your e-mail!");
                exit();
            }
            else {
                header("Location: index.php?error=Incorrect username or password");
                exit();
            }
        }
        else {
            header("Location: index.php?error=Incorrect username or password");
            exit();
        }
    }
}
else {
    header("Location: index.php");
    exit();
}