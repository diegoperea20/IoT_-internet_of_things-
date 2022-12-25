const { Router } = require("express");
const router = Router();
router.get("/suma", (req, res) => {
  res.json({ "hola": "estoy en suma" });
});
router.post("/suma", (req, res) => {
  console.log(req.body);
  json1 = req.body;
  let operador1 = json1.op1;
  let operador2 = json1.op2;
  let suma = operador1 + operador2;
  json1.suma= suma;
  if (suma > 80)
  {
    res.json("HAYY NOOO!!!!");
  }else{
    res.json("HAYY SII!!!!");
  }
  
});
module.exports = router;
