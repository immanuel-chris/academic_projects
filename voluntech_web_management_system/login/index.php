<!DOCTYPE html>
<html>
<head>
    <title>Log In to Voluntech</title>
    <?php echo '<link rel="stylesheet" href="http://'. $_SERVER['HTTP_HOST'] .'/style.css">' ?>
</head>
<?php
session_start();

if (!isset($_SESSION['id'])) {
?>
<body class="login">
    <form class="signup" action="login.php" method="post">
        <h2 class="login">VolunTech</h2>
        <?php if (isset($_GET['error'])) { ?>
            <p class="error"><?php echo $_GET['error']; ?></p>
        <?php } else if (isset($_GET['success'])) { ?>
            <p class="success"><?php echo $_GET['success']; ?></p>
        <?php } ?>
        <label>Username</label>
        <input type="text" name="username" placeholder="Username">
        
        <label>Password</label>
        <input type="password" name="password" placeholder="Password">

        <button type="submit">Sign in</button>
        <?php echo '<a href="http://'. $_SERVER['HTTP_HOST'] .'/register" class="ca">Register</a>' ?>
        <?php echo '<a href="http://'. $_SERVER['HTTP_HOST'] .'/recover_password" class="ca">Forgot Password?</a>' ?>
    </form>
</body>
<?php 
}
else {
?>
<body class="login">
    <main class="small">
        <p class="center-block">Looks like you're already signed in. Perhaps you want to go back to the dashboard?</p>
        <table class="table-fixed-width-unbordered">
            <tr>
                <td><?php echo '<button onclick="location.href=\'http://'. $_SERVER['HTTP_HOST'] .'/dashboard\';">Dashboard</button>' ?></td>
                <td><?php echo '<button onclick="location.href=\'http://'. $_SERVER['HTTP_HOST'] .'/login/logout.php\';">Log Out</button>' ?></td>
            </tr>
        </table>
    </main>
</body>
<?php 
}
?>
</html>