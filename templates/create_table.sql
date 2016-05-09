CREATE TABLE mcevent (
  eid          bigserial PRIMARY KEY,
  mcLen        integer   DEFAULT 0,
  R2           real,
  mcLund       int[],
  mcenergyCM   real[]
);
