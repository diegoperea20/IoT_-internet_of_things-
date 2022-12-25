const { Router } = require("express");
const router = Router();
router.get("/", (req, res) => {
  res.json({ temp: 23, hum: 43 });
});
router.post("/", (req, res) => {
  console.log(req.body);
  res.send("datos recibidos....");
});
module.exports = router;
