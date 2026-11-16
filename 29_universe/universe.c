//----------------------------------------------------------------------
// universe.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "body.h"
#include "universe.h"
#include "vector.h"

struct Universe {
    double radius;  // the universe spans -radius to +radius
    int n;          // number of bodies
    Body **bodies;  // the bodies
};

//----------------------------------------------------------------------

Universe *universeNew(const char *filename) {
    FILE *in = fopen(filename, "r");
    if (in == NULL) return NULL;

    int n;
    double radius;
    if (fscanf(in, "%d %lf", &n, &radius) != 2 || n < 0 || radius <= 0.0) {
        fclose(in);
        return NULL;
    }

    Universe *u = malloc(sizeof(Universe));
    u->radius = radius;
    u->n = 0;
    u->bodies = malloc(n * sizeof(Body *));
    for (int i = 0; i < n; i++) {
        double rx, ry, vx, vy, mass;
        if (fscanf(in, "%lf %lf %lf %lf %lf", &rx, &ry, &vx, &vy, &mass) != 5) {
            fclose(in);
            universeFree(u);
            return NULL;
        }
        const double r[] = {rx, ry};
        const double v[] = {vx, vy};
        u->bodies[i] = bodyNew(vectorNew(r, 2), vectorNew(v, 2), mass);
        u->n++;
    }
    fclose(in);
    return u;
}

void universeFree(Universe *u) {
    if (u == NULL) return;
    for (int i = 0; i < u->n; i++) bodyFree(u->bodies[i]);
    free(u->bodies);
    free(u);
}

void universeIncreaseTime(Universe *u, const double dt) {
    const int n = u->n;

    // Initialize the forces to zero.
    const double zero[] = {0.0, 0.0};
    Vector **f = malloc(n * sizeof(Vector *));
    for (int i = 0; i < n; i++) f[i] = vectorNew(zero, 2);

    // Compute the forces.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            Vector *force = bodyForceFrom(u->bodies[i], u->bodies[j]);
            Vector *sum = vectorPlus(f[i], force);
            vectorFree(force);
            vectorFree(f[i]);
            f[i] = sum;
        }
    }

    // Move the bodies.
    for (int i = 0; i < n; i++) {
        bodyMove(u->bodies[i], f[i], dt);
        vectorFree(f[i]);
    }
    free(f);
}

void universeDraw(const Universe *u, Draw *d) {
    drawSetXscale(d, -u->radius, u->radius);
    drawSetYscale(d, -u->radius, u->radius);
    for (int i = 0; i < u->n; i++) {
        bodyDraw(u->bodies[i], d);
    }
}
