<!DOCTYPE html>
<html>
<head>
    <title>Register to Voluntech</title>
    <?php echo '<link rel="stylesheet" href="http://'. $_SERVER['HTTP_HOST'] .'/style.css">' ?>
</head>
<?php
session_start();

if (!isset($_SESSION['id'])) {
?>
<body class="login">
    <form class="signup" action="register_check.php" method="post">
        <h2 class="login">Registration</h2>

        <?php if (isset($_GET['error'])) { ?>
            <p class="error"><?php echo $_GET['error']; ?></p>
        <?php } ?>

        <?php if (isset($_GET['success'])) { ?>
            <p class="success"><?php echo $_GET['success']; ?></p>
        <?php } ?>

        <label>E-mail<label>
        <input type="text" name="email", placeholder="E-mail"></input>

        <label>First Name</label>
        <?php if (isset($_GET['firstname'])) { ?>
            <input type="text" name="firstname" placeholder="First Name" value="<?php echo $_GET['firstname']; ?>">
        <?php }
        else { ?>
            <input type="text" name="firstname" placeholder="First Name">
        <?php }?>

        <label>Middle Name</label>
        <?php if (isset($_GET['middlename'])) { ?>
            <input type="text" name="middlename" placeholder="(Optional) Middle Name" value="<?php echo $_GET['middlename']; ?>">
        <?php }
        else { ?>
            <input type="text" name="middlename" placeholder="(Optional) Middle Name">
        <?php }?>

        <label>Family Name</label>
        <?php if (isset($_GET['familyname'])) { ?>
            <input type="text" name="familyname" placeholder="Family Name" value="<?php echo $_GET['familyname']; ?>">
        <?php }
        else { ?>
            <input type="text" name="familyname" placeholder="Family Name">
        <?php }?>

        <label>Username</label>
        <?php if (isset($_GET['username'])) { ?>
            <input type="text" name="username" placeholder="Username" value="<?php echo $_GET['username']; ?>">
        <?php }else { ?>
            <input type="text" name="username" placeholder="Username">
        <?php }?>

        <label>Birthday</label>
        <input type="date" name="birthday"></input>
        
        <label>Password</label>
        <input type="password" name="password" placeholder="Password">
        
        <label>Re-enter Password</label>
        <input type="password" name="re_password" placeholder="Re-enter Password">

        <button type="submit">Register</button>
        <?php echo '<a href="http://'. $_SERVER['HTTP_HOST'] .'/login" class="ca">Already registered?</a>' ?>
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