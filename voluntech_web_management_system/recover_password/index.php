<!DOCTYPE html>
<html>
<head>
    <title>Recover Password</title>
    <?php echo '<link rel="stylesheet" href="http://'. $_SERVER['HTTP_HOST'] .'/style.css">' ?>
</head>
<?php
session_start();

if (!isset($_SESSION['id'])) {
?>
<body class="login">
    <form class="signup" action="recover.php" method="post">
        <h2 class="login">Recover Password</h2>

        <?php if (isset($_GET['error'])) { ?>
            <p class="error"><?php echo $_GET['error']; ?></p>
        <?php } else if (isset($_GET['success'])) { ?>
            <p class="success"><?php echo $_GET['success']; ?></p>
        <?php } ?>
        
        <label>Enter Your E-mail</label>
        <input type="text" name="email" placeholder="E-mail">

        <button type="submit">Submit</button>
        <a class="ca-notice">Make sure to use the e-mail associated with your account!</a>
    </form>
</body>
<?php
}
else {
?>
<body class="login">
    <main class="small">
        <p class="center-block">You're already logged in. Perhaps you intend to change your password from the dashboard settings?</p>
        <table class="table-fixed-width-unbordered">
            <tr>
                <td><?php echo '<button onclick="location.href=\'http://'. $_SERVER['HTTP_HOST'] .'/dashboard/?page=settings\';">Settings</button>' ?></td>
                <td><?php echo '<button onclick="location.href=\'http://'. $_SERVER['HTTP_HOST'] .'/dashboard/?page=settings\';">Log Out</button>' ?></td>
            </tr>
        </table>
    </main>
</body>
<?php
}
?>