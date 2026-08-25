#!/usr/bin/node

const request = require('request');

const url = `https://swapi-api.hbtn.io/api/films/${process.argv[2]}`;

request(url, async (error, response, body) => {
  if (error) {
    console.log(error);
    return;
  }
  const characters = JSON.parse(body).characters;
  const characterPromises = characters.map(
    (characterUrl) =>
      new Promise((resolve, reject) => {
        request(characterUrl, (err, res, charBody) => {
          if (err) {
            reject(err);
            return;
          }
          resolve(JSON.parse(charBody).name);
        });
      })
  );

  try {
    const names = await Promise.all(characterPromises);
    names.forEach((name) => console.log(name));
  } catch (err) {
    console.log(err);
  }
});
