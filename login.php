<!DOCTYPE html>
<html>
<head>
  <title>Login</title>
</head>
<body>

<h2>Security Login</h2>

<input id="user" placeholder="Username">
<input id="pass" type="password" placeholder="Password">

<button onclick="login()">Login</button>

<p id="msg"></p>

<script>
function login() {
  let u = document.getElementById("user").value;
  let p = document.getElementById("pass").value;

  if (u === "admin" && p === "1234") {
    localStorage.setItem("auth", "1");
    window.location.href = "dashboard.html";
  } else {
    document.getElementById("msg").innerText = "Wrong login!";
  }
}
</script>

</body>
</html>