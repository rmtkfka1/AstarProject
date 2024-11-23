import pygame
import test

class Graphics:
    def __init__(self,windowWidth,windowHeight,cellSize):
        pygame.init()
        pygame.display.set_caption("Astart Project_202218005")  # 타이틀 변경
        self.screen = pygame.display.set_mode((windowWidth, windowHeight))
        self.font = pygame.font.Font(None, 36)
        self.running = True
        self.WHITE = (255, 255, 255)
        self.BLUE = (0, 0, 255)
        self.width = windowWidth
        self.height = windowHeight
        self.cellSize =cellSize

    def DrawGrid(self):
        for x in range(0,self.width,self.cellSize):
            pygame.draw.line(self.screen,(0,0,0),(x,0),(x,self.height))

        for y in range(0, self.height, self.cellSize):
            pygame.draw.line(self.screen, (0, 0, 0), (0, y), (self.width, y))

    def run(self):
        while self.running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.running = False

            self.screen.fill((255, 255, 255))
            self.DrawGrid()

            pygame.display.flip()

        pygame.quit()

