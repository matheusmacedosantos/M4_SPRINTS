#include <iostream>
#include <string>
#include <vector>

using namespace std;

//1 - 

float convertSensor(float size, float min_size, float max_size)
  {
    float percentage;
    percentage = (size - min_size) / (max_size - min_size);
    return percentage;
  }

//2 -
int receiveCommand()
  {
    int sensorValue;
    cin >> sensorValue;
    return sensorValue;
  }

//3-

int *insertVector(int element, int maxValue, int lastPos, int Numbers[])
  {
    int nextPos;
    nextPos = lastPos + 1;
    if ((element) > maxValue)
    {
      printf("Erro: maxValue: %d, lastPos + 1 (indice): %d\n", maxValue, nextPos);
    }
    else
    {
      Numbers[nextPos] = element;
    }
    return Numbers;
  }

//4 - 
string dirMaiorDist(int Vector[])
  {
    int maxPos = 0;
    string posList[4] = {"Right", "Left", "Front", "Back"};
    for (int i = 0; i < 5; i++)
    {
      if (Vector[i] >= Vector[maxPos])
      {
        maxPos = i;
      }
    }
  return posList[maxPos];
}



int biggestDistance(int Vector[])
  {
    int maxVal = 0;
    for (int i = 0; i < 5; i++)
    {
      if (Vector[i] >= maxVal)
      {
        maxVal = Vector[i];
      }
    }
    return maxVal;
    ;
  }

//5-

bool continue()
  {
    bool keepGoing;
    cout << "Deseja continuar o mapeamento? 0 - sim, 1 - nao:";
    cin >> keepGoing;
    return keepGoing;
  }


//6-
void printIntArray(int arrayVector[], int arrayLength)
  {
    for (int i = 0; i < arrayLength; i++)
    {
      int currElement;
      currElement = arrayVector[i];
      cout << currElement;
      cout << "\n";
    }
  }

void dirige(int initialVector[4], int maxRight, int maxLeft, int maxFront, int maxBack)
  {
    int rightPos[maxRight];
    int leftPos[maxLeft];
    int frontPos[maxFront];
    int backPos[maxBack];

    int rightLastPos = -1;
    int leftLastPos = -1;
    int frontLastPos = -1;
    int backLastPos = -1;

    insertVector(initialVector[0], maxRight, rightLastPos, rightPos);
    rightLastPos++;

    insertVector(initialVector[1], maxLeft, leftLastPos, leftPos);
    leftLastPos++;

    insertVector(initialVector[2], maxFront, frontLastPos, frontPos);
    frontLastPos++;

    insertVector(initialVector[3], maxBack, backLastPos, backPos);
    backLastPos++;

    int stop = 0;
    while (stop == 0)
    {
      int auxVector[4] = {rightPos[rightLastPos], leftPos[leftLastPos], frontPos[frontLastPos], backPos[backLastPos]};
      int maxDistance;
      int opositeDistance;
      int stepSize;
      string direcaoMaiorDistancia = dirMaiorDist(auxVector);
      cout << "Insira o n° de passos para a direcao " << direcaoMaiorDistancia << "\n";

      stepSize = receiveCommand();
      maxDistance = biggestDistance(auxVector);
      maxDistance = maxDistance - stepSize;

      if (direcaoMaiorDistancia == "Right")
      {
        auxVector[0] = maxDistance;
        auxVector[1] += stepSize;
      }
      else if (direcaoMaiorDistancia == "Left")
      {
        auxVector[1] = maxDistance;
        auxVector[0] += stepSize;
      }
      else if (direcaoMaiorDistancia == "Front")
      {
        auxVector[2] = maxDistance;
        auxVector[3] += stepSize;
      }
      else if (direcaoMaiorDistancia == "Back")
      {
        auxVector[3] = maxDistance;
        auxVector[2] += stepSize;
      }

      insertVector(auxVector[0], maxRight, rightLastPos, rightPos);
      rightLastPos++;

      insertVector(auxVector[1], maxLeft, leftLastPos, leftPos);
      leftLastPos++;

      insertVector(auxVector[2], maxFront, frontLastPos, frontPos);
      frontLastPos++;

      insertVector(auxVector[3], maxBack, backLastPos, backPos);
      backLastPos++;

      // Exibe as informações atuais nos vetores
      printf("Direcoes Right\n");
      printIntArray(rightPos, rightLastPos + 1);

      printf("Direcoes Left\n");
      printIntArray(leftPos, leftLastPos + 1);

      printf("Direcoes Front\n");
      printIntArray(frontPos, frontLastPos + 1);

      printf("Direcoes Back\n");
      printIntArray(backPos, backLastPos + 1);

      stop = continue();
    }

  printf("Posicoes Finais\n #Right:%d\n #Left:%d\n #Front:%d\n #Back:%d\n", rightPos[rightLastPos], leftPos[leftLastPos], frontPos[frontLastPos], backPos[backLastPos]);
}

int main()
{
  // Escreva os testes aqui
  int initialPos[4] = {10, 10, 10, 10};
  dirige(initialPos, 20, 20, 20, 20);
  return 0;
}